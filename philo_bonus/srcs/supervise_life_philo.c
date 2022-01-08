/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/06 15:09:28 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_died(t_philo *philo, t_data *data)
{
	int				ret;
	unsigned long	time_to_die;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	sem_wait(philo->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{
		philo->is_dead = TRUE;
		ret = TRUE;
	}
	sem_post(philo->meal_lock);
	return (ret);
}

void	*handle_death_count_meals(t_philo *philo, t_data *data)
{
	display_status(DEAD, philo, data);
	exit(DEATH);
	return (NULL);
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
		{
			if (!data->count_meals)
			{
				display_status(DEAD, philo, data);
				if (sem_close(philo->meal_lock))
					exit_error("sem_close() failed", data);
				sem_post(data->end_lock);
				return (NULL);
			}
			else
				return (handle_death_count_meals(philo, data));
		}
		usleep(100);
	}
}
