/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:15:19 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*live(void *void_data)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)void_data;
	philo = &data->philo[data->i];
	if (philo->num % 2 == 0)
	{
		while (1)
		{
			takes_forks(philo, data);
			eats(philo, data);
			releases_forks_and_sleeps(philo, data);
			thinks(philo, data);
		}
	}
	return (NULL);
}

t_bool	run_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->param[NB_OF_PHILO])
	{
		data->i = i;
		if (pthread_create(&data->philo[i].thread, NULL, live, (void *)data))
			return (FAIL);
		i++;
	}
	i = 0;
	while (i < data->param[NB_OF_PHILO])
	{
		if (pthread_join(data->philo[i++].thread, NULL))
			return (FAIL);
	}
	return (SUCCESS);
}
