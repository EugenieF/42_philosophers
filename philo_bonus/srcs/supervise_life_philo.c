/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/28 22:37:02 by EugenieFran      ###   ########.fr       */
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
	int				ret;
	unsigned long	time_to_die;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	if (philo->state == DEAD)
	{
		sem_post(philo->sem->end_lock);
		return (TRUE);
	}
	sem_wait(philo->sem->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{
		sem_post(philo->sem->meal_lock);
		display_status(DEAD, philo, data);
		sem_post(philo->sem->end_lock);
		data->philo_died = TRUE;
		philo->state = DEAD;
		ret = TRUE;
		return (ret);
	}
	sem_post(philo->sem->meal_lock);
	return (ret);
}

void	*supervise_life_philo(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	philo = &data->philo[data->i];
	while (1)
	{
		if ((data->count_meals && meals_count_reached(philo, data))
			|| philo_died(philo, data))
			return (NULL);
		usleep(100);
	}
}
