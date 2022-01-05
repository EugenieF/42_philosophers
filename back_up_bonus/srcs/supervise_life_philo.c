/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/05 11:21:48 by efrancon         ###   ########.fr       */
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
		display_status(DEAD, philo, data);
		philo->is_dead = TRUE;
		ret = TRUE;
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
		{
			if (!data->count_meals)
			{
				sem_post(data->end_lock);
				if (sem_close(philo->meal_lock))
					exit_error("sem_close() failed", data);
				return (NULL);
			}
			else
			{
				cleanup_fork(data);
				exit(DEATH);
				return (NULL);
			}
		}
		usleep(100);
	}
}
