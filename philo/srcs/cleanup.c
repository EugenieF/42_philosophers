/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/14 14:19:46 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	destroy_mutex(pthread_mutex_t *mutex)
{
	int	ret;
	int	i;

	i = 0;
	ret = pthread_mutex_destroy(mutex);
	while (ret != 0)
	{
		pthread_mutex_unlock(mutex);
		ret = pthread_mutex_destroy(mutex);
		if (i++ > 10)
			return (FAIL);
	}
	return (SUCCESS);
}

t_bool	clean_mutex(t_data *data)
{
	int	i;

	if (!destroy_mutex(&data->writing_lock)
		|| !destroy_mutex(&data->check_death_lock)
		|| !destroy_mutex(&data->count_meals_lock)
		|| !destroy_mutex(&data->end_lock))
		return (FAIL);
	i = 0;
	while (data->philo && i < data->param[NB_OF_PHILO])
	{
		if (!destroy_mutex(&data->philo[i].left_fork))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	free_status(char **status)
{
	int	i;

	if (IS_LINUX)
		i = 5;
	else
		i = 6;
	while (--i >= THINKING)
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
	if (!clean_mutex(data))
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
