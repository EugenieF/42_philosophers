/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/15 16:10:08 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	open_semaphore(
	sem_t **semaphore, char *name, int nb_of_resources, t_data *data)
{
	memset(semaphore, 0, sizeof(sem_t *));
	*semaphore = sem_open(name, O_CREAT | O_EXCL, 0777, nb_of_resources);
	if (*semaphore == SEM_FAILED)
		exit_error("sem_open()", data);
}

void	create_semaphores(t_data *data, int total_philo)
{
	int		i;

	data->sem = (t_semaphores *)ft_calloc(1, sizeof(t_semaphores));
	if (!data->sem)
		exit_error("malloc()", data);
	memset(data->sem, 0, sizeof(t_semaphores));
	unlink_semaphores();
	open_semaphore(&data->sem->forks_lock, "/sem_forks", total_philo, data);
	open_semaphore(&data->sem->writing_lock, "/sem_writing", 1, data);
	open_semaphore(&data->sem->end_lock, "/sem_end", 0, data);
	open_semaphore(&data->sem->meal_lock, "/sem_meal", 1, data);
	i = -1;
	while (++i < total_philo)
		data->philo[i].sem = data->sem;
}

void	init_philo(t_data *data)
{
	int		i;
	int		total_philo;

	total_philo = data->param[NB_OF_PHILO];
	data->philo = (t_philo *)ft_calloc(1, sizeof(t_philo) * total_philo);
	if (!data->philo)
		exit_error("malloc()", data);
	memset(data->philo, 0, sizeof(t_philo));
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
	create_semaphores(data, total_philo);
}
