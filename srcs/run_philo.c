/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/01 16:24:16 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	nobody_is_dead(t_philo *philo, t_data *data)
{
	int	ret;

	ret = TRUE;
	pthread_mutex_lock(&data->check_death);
	if (philo->state == DEAD || data->someone_died == TRUE)
		ret = FALSE;
	pthread_mutex_unlock(&data->check_death);
	return (ret);
}

void	*live(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	philo = &data->philo[data->i];
	if (philo->num % 2 == 0)
		usleep_in_ms(data->param[TIME_TO_EAT], data);
	if (pthread_create(
			&philo->check_death_thread, NULL, check_death_philo, (void *)data))
		return (NULL);
	pthread_detach(philo->check_death_thread);
	while (nobody_is_dead(philo, data))
	{
		philo_takes_forks(philo, data);
		philo_eats(philo, data);
		philo_sleeps_then_thinks(philo, data);
	}
	return (NULL);
}

t_bool	run_philo(t_data *data)
{
	int	i;

	i = 0;
	printf("  TIME IN MS\t  PHILO Nᵒ\tSTATE\n");
	printf("----------------------------------------------\n");
	while (i < data->param[NB_OF_PHILO])
	{
		data->i = i;
		if (pthread_create(
				&data->philo[i].life_thread, NULL, live, (void *)data))
			return (FAIL);
		pthread_detach(data->philo[i].life_thread);
		usleep(100);
		i++;
	}
	i = 0;
	while (data->someone_died == FALSE)
		usleep_in_ms(100, data);
	return (SUCCESS);
}
