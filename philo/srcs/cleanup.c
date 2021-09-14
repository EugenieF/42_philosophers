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

t_bool	destroy_mutex(t_data *data)
{
	int	i;
	int	ret;

	ret = pthread_mutex_destroy(&data->writing_lock);
	if (ret != 0)
	{
		pthread_mutex_unlock(&data->writing_lock);
		if (pthread_mutex_destroy(&data->writing_lock) != 0)
			return (FAIL);
	}
	ret = pthread_mutex_destroy(&data->check_death_lock);
	if (ret != 0)
	{
		pthread_mutex_unlock(&data->check_death_lock);
		if (pthread_mutex_destroy(&data->check_death_lock) != 0)
			return (FAIL);
	}
	ret = pthread_mutex_destroy(&data->count_meals_lock);
	if (ret != 0)
	{
		pthread_mutex_unlock(&data->count_meals_lock);
		if (pthread_mutex_destroy(&data->count_meals_lock) != 0)
			return (FAIL);
	}
	ret = pthread_mutex_destroy(&data->end_lock);
	if (ret != 0)
	{
		pthread_mutex_unlock(&data->end_lock);
		if (pthread_mutex_destroy(&data->end_lock) != 0)
			return (FAIL);
	}
	i = 0;
	while (data->philo && i < data->param[NB_OF_PHILO])
	{
		ret = pthread_mutex_destroy(&data->philo[i].left_fork);
		if (ret != 0)
		{
			pthread_mutex_unlock(&data->philo[i].left_fork);
			if (pthread_mutex_destroy(&data->philo[i].left_fork) != 0)
				return (FAIL);
		}
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
