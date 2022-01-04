/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/04 11:32:18 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	open_semaphore(
	sem_t **semaphore, char *name, int nb_of_resources, t_data *data)
{
	memset(semaphore, 0, sizeof(sem_t *));
	*semaphore = sem_open(name, O_CREAT | O_EXCL, 0666, nb_of_resources);
	if (*semaphore == SEM_FAILED)
		exit_error("sem_open() failed", data);
}

void	create_semaphores(t_data *data, int total_philo)
{
	unlink_semaphores();
	open_semaphore(&data->forks_lock, "/sem_forks", total_philo, data);
	open_semaphore(&data->writing_lock, "/sem_writing", 1, data);
	open_semaphore(&data->data_lock, "/sem_data", 1, data);
	open_semaphore(&data->end_lock, "/sem_end", 0, data);
}

void	init_philo(t_data *data)
{
	int		i;
	int		total_philo;
	char	*num_str;

	total_philo = data->param[NB_OF_PHILO];
	data->philo = (t_philo *)ft_calloc(1, sizeof(t_philo) * total_philo);
	if (!data->philo)
		exit_error("malloc() failed", data);
	memset(data->philo, 0, sizeof(t_philo));
	data->start_time = get_time();
	i = 0;
	while (i < total_philo)
	{
		data->philo[i].last_meal = data->start_time;
		data->philo[i].nb_of_meals = 0;
		data->philo[i].num = i + 1;
		data->philo[i].is_dead = FALSE;
		num_str = ft_itoa(i + 1);
		data->philo[i].sem_name = ft_strjoin("/sem_meal", num_str);
		clean_free(&num_str);
		i++;
	}
	create_semaphores(data, total_philo);
}
