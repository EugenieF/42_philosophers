/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 13:17:02 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	program_is_still_running(t_data *data)
{
	pthread_mutex_lock(&data->count_meals_lock);
	if (data->count_meals > data->param[NB_OF_PHILO])
	{
		pthread_mutex_unlock(&data->count_meals_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&data->count_meals_lock);
	pthread_mutex_lock(&data->check_death_lock);
	if (data->someone_died == TRUE)
	{
		pthread_mutex_unlock(&data->check_death_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&data->check_death_lock);
	return (TRUE);
}

void	wait_until_the_end(t_data *data)
{
	while (program_is_still_running(data))
		usleep_in_ms(10, data);
	if (data->count_meals == data->param[NB_OF_PHILO] + 1)
	{
		printf("\n    All %d philosophers ", data->param[NB_OF_PHILO]);
		printf("ate their %d meals\n", data->param[NB_OF_MEALS]);
	}
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
		usleep(1000);
		i++;
	}
	wait_until_the_end(data);
	return (SUCCESS);
}
