/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/06 14:52:07 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_exit_status(void *void_data)
{
	int		i;
	int		exit_status;
	t_data	*data;

	data = (t_data *)void_data;
	i = 0;
	while (1)
	{
		exit_status = 0;
		waitpid(data->philo[i].pid, &exit_status, WNOHANG);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		if (exit_status == MEALS_REACHED)
			data->count_meals++;
		if (exit_status == DEATH
			|| data->count_meals > data->param[NB_OF_PHILO])
		{
			sem_post(data->end_lock);
			return (NULL);
		}
		i++;
		i = i % data->param[NB_OF_PHILO];
		usleep(100);
	}
}

void	waiting_for_the_end(t_data *data)
{
	int			i;
	pthread_t	meals_thread;

	if (data->count_meals)
	{
		if (pthread_create(
				&meals_thread, NULL, check_exit_status, (void *)data))
			exit_error("pthread_create() failed", data);
		if (pthread_detach(meals_thread))
			exit_error("pthread_detach() failed", data);
	}
	sem_wait(data->end_lock);
	i = 0;
	while (i < data->param[NB_OF_PHILO])
		kill(data->philo[i++].pid, SIGKILL);
	if (data->count_meals == data->param[NB_OF_PHILO] + 1)
	{
		printf("\n    All %d philosophers ", data->param[NB_OF_PHILO]);
		printf("ate their %d meals\n", data->param[NB_OF_MEALS]);
	}
}

void	run_philo(t_data *data)
{
	int	i;

	i = 0;
	printf("  TIME IN MS\t  PHILO Nᵒ\tSTATE\n");
	printf("----------------------------------------------\n");
	while (i < data->param[NB_OF_PHILO])
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
			exit_error("fork() failed", data);
		else if (data->philo[i].pid == CHILD)
			live(&data->philo[i], data);
		usleep(1000);
		i++;
	}
	waiting_for_the_end(data);
}
