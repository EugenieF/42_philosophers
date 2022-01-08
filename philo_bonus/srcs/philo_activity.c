/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/08 15:29:26 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_takes_forks(t_philo *philo, t_data *data)
{
	sem_wait(data->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	if (data->param[NB_OF_PHILO] == 1)
	{
		usleep_in_ms(data->param[TIME_TO_DIE] + 100);
		return (FAIL);
	}
	sem_wait(data->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	return (SUCCESS);
}

void	philo_eats(t_philo *philo, t_data *data)
{
	sem_wait(philo->meal_lock);
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	sem_post(philo->meal_lock);
	display_status(EATING, philo, data);
	usleep_in_ms(data->param[TIME_TO_EAT]);
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	sem_post(data->forks_lock);
	sem_post(data->forks_lock);
	display_status(SLEEPING, philo, data);
	usleep_in_ms(data->param[TIME_TO_SLEEP]);
	if (had_enough_meals(philo, data))
		return ;
	display_status(THINKING, philo, data);
	usleep(1000);
}
