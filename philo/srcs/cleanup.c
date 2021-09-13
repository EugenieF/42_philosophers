/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/11 13:57:20 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_unlock(&data->writing_lock);
	pthread_mutex_unlock(&data->end_lock);
	pthread_mutex_unlock(&data->count_meals_lock);
	pthread_mutex_unlock(&data->check_death_lock);
	if (pthread_mutex_destroy(&data->writing_lock) != 0
		|| pthread_mutex_destroy(&data->check_death_lock) != 0
		|| pthread_mutex_destroy(&data->count_meals_lock) != 0
		|| pthread_mutex_destroy(&data->end_lock) != 0 )
		return (FAIL);
	i = 0;
	while (i < data->param[NB_OF_PHILO])
	{
		pthread_mutex_unlock(&data->philo[i].left_fork);
		if (pthread_mutex_destroy(&data->philo[i].left_fork) != 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	free_status(char **status)
{
	int	i;

	i = 0;
	while (++i < 6)
	{
		if (status[i])
		{
			free(status[i]);
			status[i] = NULL;
		}
	}
	free(status);
	status = NULL;
}

t_bool	cleanup(t_data *data)
{
	if (!data)
		return (SUCCESS);
	if (!destroy_mutex(data))
		return (FAIL);
	if (data->status)
		free_status(data->status);
	if (data->philo)
		free(data->philo);
	if (data->param)
		free(data->param);
	free(data);
	return (SUCCESS);
}
