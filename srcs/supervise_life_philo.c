/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <efrancon@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 13:30:55 by EugenieFr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	meals_count_reached(t_data *data)
{
	pthread_mutex_lock(&data->count_meals_lock);
	if (data->count_meals > data->param[NB_OF_PHILO])
	{
		pthread_mutex_unlock(&data->count_meals_lock);
		pthread_mutex_unlock(&data->end_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&data->count_meals_lock);
	return (FALSE);
}

t_bool	philo_died(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->check_death_lock);
	if ((long)data->param[TIME_TO_DIE] < get_time(data) - philo->last_meal)
	{
		display_status(DEAD, philo, data);
		data->someone_died = TRUE;
		philo->state = DEAD;
		pthread_mutex_unlock(&data->check_death_lock);
		pthread_mutex_unlock(&data->end_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&data->check_death_lock);
	return (FALSE);
}

void	*supervise_life_philo(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	philo = &data->philo[data->i];
	while (1)
	{
		if (data->count_meals && meals_count_reached(data))
			return (NULL);
		if (philo->state != DEAD && philo_died(philo, data))
			return (NULL);
		usleep_in_ms(1, data);
	}
}
