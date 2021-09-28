/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/28 22:32:35 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_exit_status(void *void_data)
{
	int		i;
	int		exit_status;
	t_data	*data;

	data = (t_data *)void_data;
	i = -1;
	while (1)
	{
		exit_status = 0;
		waitpid(data->philo[++i].pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		if (exit_status == MEALS_REACHED)
			data->count_meals++;
		if (data->count_meals > data->param[NB_OF_PHILO]
			|| exit_status == DEATH)
		{
			sem_post(data->sem->end_lock);
			return (NULL);
		}
		i = i % data->param[NB_OF_PHILO];
		usleep(50);
	}
}

t_bool	waiting_for_the_end(t_data *data)
{
	int			i;
	pthread_t	meals_thread;

	if (data->count_meals)
	{
		if (pthread_create(
				&meals_thread, NULL, check_exit_status, (void *)data))
			return (FAIL);
		if (pthread_detach(meals_thread))
			return (FAIL);
	}
	sem_wait(data->sem->end_lock);
	i = 0;
	while (i < data->param[NB_OF_PHILO])
		kill(data->philo[i++].pid, SIGKILL);
	if (data->count_meals == data->param[NB_OF_PHILO] + 1)
	{
		printf("\n    All %d philosophers ", data->param[NB_OF_PHILO]);
		printf("ate their %d meals\n", data->param[NB_OF_MEALS]);
	}
	return (SUCCESS);
}

t_bool	run_philo(t_data *data)
{
	int	i;
	int	exit_status;

	i = 0;
	printf("  TIME IN MS\t  PHILO Nᵒ\tSTATE\n");
	printf("----------------------------------------------\n");
	while (i < data->param[NB_OF_PHILO])
	{
		data->i = i;
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
			return (FAIL);
		else if (data->philo[i].pid == CHILD)
		{
			exit_status = live(&data->philo[i], data);
			if (exit_status == FAIL)
				return (FAIL);
			exit(exit_status);
		}
		usleep(100);
		i++;
	}
	if (!waiting_for_the_end(data))
		return (FAIL);
	return (SUCCESS);
}
