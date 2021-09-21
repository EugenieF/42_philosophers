/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/21 12:55:05 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	waiting_for_the_end(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->end_lock);
	while (++i < data->param[NB_OF_PHILO])
	{
		if (pthread_join(data->philo[i].life_thread, NULL))
			return (FAIL);
	}
	if (data->count_meals > data->param[NB_OF_PHILO])
	{
		printf("\n    All %d philosophers ", data->param[NB_OF_PHILO]);
		printf("ate their %d meals\n", data->param[NB_OF_MEALS]);
	}
	return (SUCCESS);
}

t_bool	run_philo(t_data *data)
{
	int	i;

	i = 0;
	printf("  TIME IN MS\t  PHILO Nᵒ\tSTATE\n");
	printf("----------------------------------------------\n");
	while (i < data->param[NB_OF_PHILO])
	{
		pthread_mutex_lock(&data->data_lock);
		data->i = i;
		pthread_mutex_unlock(&data->data_lock);
		if (pthread_create(
				&data->philo[i].life_thread, NULL, live, (void *)data))
			return (FAIL);
		usleep(100);
		i++;
	}
	if (!waiting_for_the_end(data))
		return (FAIL);
	return (SUCCESS);
}
