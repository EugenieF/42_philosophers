/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:04:57 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/01 16:23:58 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_just_died(t_philo *philo, t_data *data)
{
	return ((long)data->param[TIME_TO_DIE] < get_time(data) - philo->last_meal);
}

void	*check_death_philo(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	philo = &data->philo[data->i];
	while (1)
	{
		pthread_mutex_lock(&data->check_death);
		if (philo->state != DEAD && philo_just_died(philo, data))
		{
			display_status(DEAD, philo, data);
			data->someone_died = TRUE;
			philo->state = DEAD;
			pthread_mutex_unlock(&data->check_death);
			pthread_mutex_unlock(&data->death_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->check_death);
		usleep_in_ms(1, data);
	}
}
