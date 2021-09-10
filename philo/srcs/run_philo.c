/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/10 12:26:06 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	waiting_for_the_end(t_data *data)
{
	pthread_mutex_lock(&data->end_lock);
	if (data->count_meals > data->param[NB_OF_PHILO])
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
		usleep(100);
		i++;
	}
	waiting_for_the_end(data);
	return (SUCCESS);
}
