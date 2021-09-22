/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/17 13:31:10 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlink_semaphores(void)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_writing");
	sem_unlink("/sem_end");
	sem_unlink("/sem_death");
	sem_unlink("/sem_state");
}

t_bool	close_semaphores(t_data *data)
{
	if (sem_close(data->sem->forks_lock) != 0
		|| sem_close(data->sem->writing_lock) != 0
		|| sem_close(data->sem->end_lock) != 0
		|| sem_close(data->sem->state_lock) != 0
		|| sem_close(data->sem->check_death_lock) != 0)
		return (FAIL);
	unlink_semaphores();
	if (data->sem)
		free(data->sem);
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
	if (data->status)
		free_status(data->status);
	if (data->philo)
	{
		if (!close_semaphores(data))
			return (FAIL);
		free(data->philo);
	}
	if (data->param)
		free(data->param);
	free(data);
	return (SUCCESS);
}
