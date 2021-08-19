/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <efrancon@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:47 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:23:49 by EugenieFr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	takes_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->left_fork);
	display_status(HAS_A_FORK, philo, data);
	pthread_mutex_lock(philo->right_fork);
	display_status(HAS_A_FORK, philo, data);
}

void	eats(t_philo *philo, t_data *data)
{
	philo->last_meal = get_time(data);
	display_status(EATING, philo, data);
	usleep(data->param[TIME_TO_EAT] * 1000);
}

void	releases_forks_and_sleeps(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display_status(SLEEPING, philo, data);
	usleep(data->param[TIME_TO_SLEEP] * 1000);
}

void	thinks(t_philo *philo, t_data *data)
{
	display_status(THINKING, philo, data);
	usleep(data->param[TIME_TO_DIE]);
}
