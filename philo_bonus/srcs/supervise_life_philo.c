/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/09 12:54:35 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	meals_count_reached(t_philo *philo, t_data *data)
{
	if (data->count_meals == NO_NEED)
		return (FALSE);
	if (philo->nb_of_meals >= data->param[NB_OF_MEALS])
	{
		data->meals_reached = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	philo_died(t_philo *philo, t_data *data)
{
	unsigned long	time_to_die;

	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	if (time_to_die < get_time() - philo->last_meal
		&& philo->state != EATING)
	{
		display_status(DEAD, philo, data);
		data->philo_died = TRUE;
		philo->state = DEAD;
		sem_post(philo->end_lock);
		return (TRUE);
	}
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
		if (data->count_meals && meals_count_reached(philo, data))
			return (NULL);
		if (philo->state != DEAD && philo_died(philo, data))
			return (NULL);
		usleep(10);
	}
}
