/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/21 11:29:25 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	program_completed(t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->data_lock);
	if (data->finish == data->param[NB_OF_PHILO])
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}

static void	waiting_for_the_end(t_data *data)
{
	int	i;

	while (!program_completed(data))
		usleep(100);
	i = -1;
	while (++i < data->param[NB_OF_PHILO])
	{
		if (pthread_join(data->philo[i].life_thread, NULL))
			exit_error("pthread_join() failed", data);
	}
	if (data->need_count_meals && data->count_meals >= data->param[NB_OF_PHILO])
	{
		printf("\n    All %d philosophers ", data->param[NB_OF_PHILO]);
		printf("ate their %d meals\n", data->param[NB_OF_MEALS]);
	}
}

void	run_philo(t_data *data)
{
	int	i;

	i = 0;
	printf("  TIME IN MS\t  PHILO Nᵒ\tSTATE\n");
	printf("----------------------------------------------\n");
	while (i < data->param[NB_OF_PHILO])
	{
		lock_mutex(&data->data_lock);
		data->i = i;
		unlock_mutex(&data->data_lock);
		if (pthread_create(
				&data->philo[i].life_thread, NULL, live, (void *)data))
			exit_error("pthread_create() failed", data);
		usleep(1000);
		i++;
	}
	waiting_for_the_end(data);
}
