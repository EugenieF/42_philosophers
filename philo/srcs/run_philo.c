/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/15 14:29:10 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	program_completed(t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->data_lock);
	if (data->finish == data->param[NB_OF_PHILO])
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}

t_bool	waiting_for_the_end(t_data *data)
{
	int	i;

	while (!program_completed(data))
		usleep(10);
	i = -1;
	while (++i < data->param[NB_OF_PHILO])
	{
		// printf("%d\n", i);
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
