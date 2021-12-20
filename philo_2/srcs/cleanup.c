/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/16 19:42:12 by efrancon         ###   ########.fr       */
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
		|| !destroy_mutex(&data->data_lock))
		return (FAIL);
	i = 0;
	while (data->philo && i < data->param[NB_OF_PHILO])
	{
		if (!destroy_mutex(&data->philo[i].left_fork)
			|| !destroy_mutex(&data->philo[i].meal_lock))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	free_status(t_data *data)
{
	int	i;

	i = -1;
	while (data->status[++i])
	{
		if (data->status[i])
			clean_free(&data->status[i]);
	}
	free(data->status);
	data->status = NULL;
}

static void	exit_error_cleanup(char *message, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(" failed\n", 2);
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->param)
	{
		free(data->param);
		data->param = NULL;
	}
	free(data);
	data = NULL;
	exit(EXIT_FAILURE);
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	if (!clean_mutex(data))
		exit_error_cleanup("pthread_mutex_destroy()", data);
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->status)
		free_status(data);
	if (data->param)
	{
		free(data->param);
		data->param = NULL;
	}
	free(data);
	data = NULL;
}
