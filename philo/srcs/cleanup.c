/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/21 13:04:01 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	destroy_mutex(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_destroy(mutex);
	if (ret != 0)
			return (FAIL);
	return (SUCCESS);
}

t_bool	clean_mutex(t_data *data)
{
	int	i;

	if (!destroy_mutex(&data->writing_lock)
		|| !destroy_mutex(&data->count_meals_lock)
		|| !destroy_mutex(&data->data_lock))
		return (FAIL);
	i = 0;
	while (data->philo && i < data->param[NB_OF_PHILO])
	{
		if (!destroy_mutex(&data->philo[i].left_fork)
			|| !destroy_mutex(&data->philo[i].state_lock)
			|| !destroy_mutex(&data->philo[i].meal_lock))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	free_status(t_data *data)
{
	int	i;

	if (IS_LINUX)
		i = 5;
	else
		i = 6;
	while (--i >= THINKING)
	{
		if (data->status[i])
			free(data->status[i]);
	}
	free(data->status);
	data->status = NULL;
}

t_bool	cleanup(t_data *data)
{
	if (!data)
		return (SUCCESS);
	if (!clean_mutex(data))
		return (FAIL);
	if (data->philo)
		free(data->philo);
	if (data->status)
		free_status(data);
	if (data->param)
		free(data->param);
	free(data);
	return (SUCCESS);
}
