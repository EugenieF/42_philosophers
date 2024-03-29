/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/08 18:56:00 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	close_semaphores(t_data *data)
{
	if (sem_close(data->forks_lock) != 0
		|| sem_close(data->writing_lock) != 0)
		return (FAIL);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_writing");
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

void	free_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->param[NB_OF_PHILO])
	{
		sem_unlink(data->philo[i].sem_meal_name);
		sem_unlink(data->philo[i].sem_end_name);
		clean_free(&data->philo[i].sem_meal_name);
		clean_free(&data->philo[i].sem_end_name);
	}
	free(data->philo);
	data->philo = NULL;
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	if (data->philo)
	{
		if (!close_semaphores(data))
			exit_error_cleanup("sem_close()", data);
		free_philo(data);
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
