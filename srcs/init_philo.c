/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <efrancon@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:54 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:23:56 by EugenieFr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	link_right_fork_mutex(t_data *data)
{
	int	i;
	int	last_philo;

	last_philo = data->param[NB_OF_PHILO] - 1;
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
		data->philo[i].num = i + 1;
		i++;
	}
	if (!create_left_fork_mutex(data))
		return (FAIL);
	link_right_fork_mutex(data);
	return (SUCCESS);
}
