/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/01 12:28:11 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	link_right_fork_mutex(t_data *data)
{
	int	i;
	int	last_philo;

	last_philo = data->param[NB_OF_PHILO] - 1;
	if (data->param[NB_OF_PHILO] == 1)
		data->philo[0].right_fork = NULL;
	else
		data->philo[0].right_fork = &data->philo[last_philo].left_fork;
	i = -1;
	while (++i < last_philo)
		data->philo[i + 1].right_fork = &data->philo[i].left_fork;
}

t_bool	create_left_fork_mutex(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->param[NB_OF_PHILO])
	{
		ret = pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (ret)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

t_bool	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->param[NB_OF_PHILO]);
	if (!data->philo)
		return (FAIL);
	while (i < data->param[NB_OF_PHILO])
	{
		data->philo[i].state = THINKING;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].num = i + 1;
		i++;
	}
	data->someone_died = FALSE;
	if (!create_left_fork_mutex(data))
		return (FAIL);
	link_right_fork_mutex(data);
	return (SUCCESS);
}
