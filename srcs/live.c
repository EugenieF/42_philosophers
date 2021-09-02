/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <efrancon@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 13:31:02 by EugenieFr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	nobody_is_dead(t_philo *philo, t_data *data)
{
	int	ret;

	ret = TRUE;
	pthread_mutex_lock(&data->check_death_lock);
	if (philo->state == DEAD || data->someone_died == TRUE)
		ret = FALSE;
	pthread_mutex_unlock(&data->check_death_lock);
	return (ret);
}

t_bool	not_enough_meals(t_philo *philo, t_data *data)
{
	if (data->count_meals == NO_NEED)
		return (TRUE);
	pthread_mutex_lock(&data->count_meals_lock);
	if (philo->nb_of_meals < data->param[NB_OF_MEALS])
	{
		pthread_mutex_unlock(&data->count_meals_lock);
		return (TRUE);
	}
	data->count_meals++;
	pthread_mutex_unlock(&data->count_meals_lock);
	return (FALSE);
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
			&philo->life_insurance, NULL, supervise_life_philo, (void *)data))
		return (NULL);
	pthread_detach(philo->life_insurance);
	while (not_enough_meals(philo, data) && nobody_is_dead(philo, data))
	{
		philo_takes_forks(philo, data);
		philo_eats(philo, data);
		philo_sleeps_then_thinks(philo, data);
	}
	return (NULL);
}
