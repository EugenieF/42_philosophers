/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/09 12:29:22 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	open_semaphores(t_data *data, int total_philo)
{
	int		i;
	sem_t	*forks_lock;
	sem_t	*writing_lock;

	unlink_semaphores();
	forks_lock = sem_open("/sem_forks", O_CREAT | O_EXCL, 0777, total_philo);
	writing_lock = sem_open("/sem_writing", O_CREAT | O_EXCL, 0777, 1);
	data->end_lock = sem_open("/sem_end", O_CREAT | O_EXCL, 0777, 0);
	if (forks_lock == SEM_FAILED || writing_lock == SEM_FAILED)
		return (FAIL);
	i = -1;
	while (++i < total_philo)
	{
		data->philo[i].forks_lock = forks_lock;
		data->philo[i].writing_lock = writing_lock;
		data->philo[i].end_lock = data->end_lock;
	}
	return (SUCCESS);
}

t_bool	init_philo(t_data *data)
{
	int		i;
	int		total_philo;

	total_philo = data->param[NB_OF_PHILO];
	data->philo = (t_philo *)malloc(sizeof(t_philo) * total_philo);
	if (!data->philo)
		return (FAIL);
	data->start_time = get_time();
	i = 0;
	while (i < total_philo)
	{
		data->philo[i].state = THINKING;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].nb_of_meals = 0;
		data->philo[i].num = i + 1;
		i++;
	}
	if (!open_semaphores(data, total_philo))
		return (FAIL);
	return (SUCCESS);
}
