/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/12 22:22:57 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	philo_died(t_philo *philo, t_data *data)
{
	unsigned long	time_to_die;

	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	sem_wait(philo->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{
		sem_post(philo->meal_lock);
		sem_wait(philo->end_lock);
		philo->is_dead = TRUE;
		philo->end = TRUE;
		sem_post(philo->end_lock);
		return (TRUE);
	}
	sem_post(philo->meal_lock);
	return (FALSE);
}

static t_bool	had_enough_meals(t_philo *philo, t_data *data)
{
	t_bool	ret;

	ret = FALSE;
	sem_wait(philo->meal_lock);
	if (data->count_meals == NEEDED
		&& philo->nb_of_meals >= data->param[NB_OF_MEALS])
	{
		ret = TRUE;
		sem_wait(philo->end_lock);
		philo->end = TRUE;
		sem_post(philo->end_lock);
	}
	sem_post(philo->meal_lock);
	return (ret);
}

void	*supervise_life_philo(void *void_philo)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)void_philo;
	data = philo->data;
	while (1)
	{
		if (philo_died(philo, data))
			return (NULL);
		if (had_enough_meals(philo, data))
			return ((void *)1);
		usleep(100);
	}
}
