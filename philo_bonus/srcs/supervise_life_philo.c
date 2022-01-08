/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/07 22:20:17 by efrancon         ###   ########.fr       */
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
		ret = TRUE;
	sem_post(philo->meal_lock);
	return (ret);
}

void	*supervise_life_philo(void *void_philo)
{
	t_data		*data;
	t_philo		*philo;
	int			i;

	i = -1;
	philo = (t_philo *)void_philo;
	data = philo->data;
	while (1)
	{
		if (philo_died(philo, data))
		{
			display_status(DEAD, philo, data);
			sem_close(philo->meal_lock);
			sem_close(data->forks_lock);
			sem_close(data->data_lock);
			// sem_post(data->writing_lock);
			// sem_close(data->writing_lock);
			exit(DEATH);
			return (NULL);
		}
		usleep(100);
	}
}
