/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/16 12:09:57 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	open_semaphore(sem_t **semaphore, char *name, int nb_of_resources)
{
	*semaphore = sem_open(name, O_CREAT | O_EXCL, 0777, nb_of_resources);
	if (*semaphore == SEM_FAILED)
		return (FAIL);
	return (SUCCESS);
}

t_bool	create_semaphores(t_data *data, int total_philo)
{
	int		i;

	unlink_semaphores();
	if (!open_semaphore(&data->sem->forks_lock, "/sem_forks", total_philo)
		|| !open_semaphore(&data->sem->writing_lock, "/sem_writing", 1)
		|| !open_semaphore(&data->sem->end_lock, "/sem_end", 0))
		return (FAIL);
	i = -1;
	while (++i < total_philo)
		data->philo[i].sem = data->sem;
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
	if (!create_semaphores(data, total_philo))
		return (FAIL);
	return (SUCCESS);
}
