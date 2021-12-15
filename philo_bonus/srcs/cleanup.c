/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/15 14:51:20 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlink_semaphores(void)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_writing");
	sem_unlink("/sem_end");
	sem_unlink("/sem_meal");
}

t_bool	close_semaphores(t_data *data)
{
	if (sem_close(data->sem->forks_lock) != 0
		|| sem_close(data->sem->writing_lock) != 0
		|| sem_close(data->sem->end_lock) != 0
		|| sem_close(data->sem->meal_lock) != 0)
		return (FAIL);
	unlink_semaphores();
	if (data->sem)
	{
		free(data->sem);
		data->sem = NULL;
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
	if (data->status)
		free_status(data);
	if (data->philo)
	{
		if (!close_semaphores(data))
			exit_error_cleanup("sem_close()", data);
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
}
