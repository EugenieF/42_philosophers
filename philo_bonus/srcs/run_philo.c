/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/08 22:28:14 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_exit_status(t_data *data)
{
	int		i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	waitpid(-1, &exit_status, 0);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	if (exit_status == MEALS_REACHED)
	{
		data->count_meals++;
		if (data->count_meals <= data->param[NB_OF_PHILO])
			check_exit_status(data);
	}
}

static void	end_philo(t_data *data)
{
	int			i;

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
	check_exit_status(data);
	end_philo(data);
}
