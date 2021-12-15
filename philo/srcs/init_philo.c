/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/15 16:03:43 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	link_right_fork_mutex(t_data *data)
{
	int	i;
	int	y;
	int	nb_philos;

	nb_philos = data->param[NB_OF_PHILO];
	if (nb_philos == 1)
		data->philo[0].right_fork = NULL;
	else
	{
		i = -1;
		while (++i < nb_philos)
		{
			y = (i + 1) % nb_philos;
			data->philo[i].right_fork = &data->philo[y].left_fork;
		}
	}
}

t_bool	create_left_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->param[NB_OF_PHILO])
	{
		if (pthread_mutex_init(&data->philo[i].left_fork, NULL)
			|| pthread_mutex_init(&data->philo[i].state_lock, NULL)
			|| pthread_mutex_init(&data->philo[i].meal_lock, NULL))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_philo *)ft_calloc(
			1, sizeof(t_philo) * data->param[NB_OF_PHILO]);
	if (!data->philo)
		exit_error("malloc()", data);
	memset(data->philo, 0, sizeof(t_philo));
	data->start_time = get_time();
	while (i < data->param[NB_OF_PHILO])
	{
		data->philo[i].state = THINKING;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].nb_of_meals = 0;
		data->philo[i].done = 0;
		data->philo[i].num = i + 1;
		i++;
	}
	data->someone_died = FALSE;
	if (!create_left_fork_mutex(data))
		exit_error("pthread_mutex_init()", data);
	link_right_fork_mutex(data);
}
