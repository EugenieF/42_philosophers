/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/11 11:54:05 by efrancon         ###   ########.fr       */
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
	sem_unlink("/sem_forks");
	sem_unlink("/sem_writing");
	open_semaphore(&data->forks_lock, "/sem_forks", total_philo, data);
	open_semaphore(&data->writing_lock, "/sem_writing", 1, data);
}

void	fill_philo(int i, t_data *data)
{
	char	*num_str;

	data->philo[i].last_meal = data->start_time;
	data->philo[i].nb_of_meals = 0;
	data->philo[i].num = i + 1;
	data->philo[i].end = FALSE;
	data->philo[i].is_dead = FALSE;
	num_str = ft_itoa(i + 1);
	data->philo[i].sem_meal_name = ft_strjoin("/sem_meal", num_str);
	data->philo[i].sem_end_name = ft_strjoin("/sem_end", num_str);
	data->philo[i].data = data;
	clean_free(&num_str);
}

void	get_time_to_think(int time_to_eat, int time_to_sleep, t_data *data)
{
	if (data->param[NB_OF_PHILO] % 2 == 0)
		data->param[TIME_TO_THINK] = time_to_eat - time_to_sleep;
	else
		data->param[TIME_TO_THINK] = 2 * time_to_eat - time_to_sleep;
	if (data->param[TIME_TO_THINK] < 0 || time_to_sleep > time_to_eat)
		data->param[TIME_TO_THINK] = 0;
	data->simultaneous_meals = data->param[NB_OF_PHILO] / 2;
}

void	init_philo(t_data *data)
{
	int		i;
	int		total_philo;

	total_philo = data->param[NB_OF_PHILO];
	data->philo = (t_philo *)ft_calloc(1, sizeof(t_philo) * total_philo);
	if (!data->philo)
		exit_error("malloc() failed", data);
	memset(data->philo, 0, sizeof(t_philo));
	data->start_time = get_time();
	i = 0;
	while (i < total_philo)
	{
		fill_philo(i, data);
		i++;
	}
	create_semaphores(data, total_philo);
	get_time_to_think(
		data->param[TIME_TO_EAT], data->param[TIME_TO_SLEEP], data);
}
