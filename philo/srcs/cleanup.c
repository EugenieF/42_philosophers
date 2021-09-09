/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:49 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/04 16:43:15 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(int nb_of_philo, t_philo *philo)
{
	int	i;

	if (!philo)
		return ;
	i = 0;
	while (i < nb_of_philo)
		pthread_mutex_destroy(&philo[i++].left_fork);
	free(philo);
	philo = NULL;
}

void	destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->writing_lock);
	pthread_mutex_destroy(&data->check_death_lock);
	pthread_mutex_destroy(&data->count_meals_lock);
	pthread_mutex_destroy(&data->end_lock);
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	destroy_mutex(data);
	if (data->philo)
		free_philo(data->param[NB_OF_PHILO], data->philo);
	if (data->status)
	{
		free(data->status);
		data->status = NULL;
	}
	if (data->param)
	{
		free(data->param);
		data->param = NULL;
	}
	free(data);
	data = NULL;
}
