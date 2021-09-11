/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/11 13:32:54 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlink_semaphores(void)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_writing");
	sem_unlink("/sem_end");
}

t_bool	close_semaphores(t_data *data)
{
	if (sem_close(data->forks_lock) != 0
		|| sem_close(data->writing_lock) != 0
		|| sem_close(data->end_lock) != 0)
		return (FAIL);
	unlink_semaphores();
	return (SUCCESS);
}

void	free_status(char **status)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		free(status[i]);
		status[i++] = NULL;
	}
	free(status);
	status = NULL;
}

t_bool	cleanup(t_data *data)
{
	if (!data)
		return (SUCCESS);
	if (data->philo)
	{
		if (!close_semaphores(data))
			return (FAIL);
		free(data->philo);
	}
	if (data->param)
		free(data->param);
	if (data->status)
		free_status(data->status);
	free(data);
	return (SUCCESS);
}
