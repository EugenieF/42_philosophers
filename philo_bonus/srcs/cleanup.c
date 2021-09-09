/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/09 13:02:24 by EugenieFran      ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < data->param[NB_OF_PHILO])
	{
		sem_close(data->philo[i].forks_lock);
		sem_close(data->philo[i++].writing_lock);
		sem_close(data->philo[i++].end_lock);
	}
	sem_close(data->end_lock);
	unlink_semaphores();
	return (SUCCESS);
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
		data->philo = NULL;
	}
	if (data->status)
	{
		free(data->status);
		data->status = NULL;
	}
	if (data->param)
	{
		free(data->param);
		data->param = NULL;
	}
	free(data);
	data = NULL;
	return (SUCCESS);
}
