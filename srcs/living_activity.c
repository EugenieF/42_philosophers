/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living_activity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 22:23:47 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/01 16:17:15 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_takes_forks(t_philo *philo, t_data *data)
{
	if (philo->state == THINKING && pthread_mutex_lock(&philo->left_fork) == 0)
		display_status(HAS_A_FORK, philo, data);
	if (!philo->right_fork)
		return (usleep_in_ms(data->param[TIME_TO_DIE], data));
	if (philo->state == HAS_A_FORK
		&& pthread_mutex_lock(philo->right_fork) == 0)
	{
		display_status(HAS_A_FORK, philo, data);
		philo->state = HAS_TWO_FORKS;
	}
}

void	philo_eats(t_philo *philo, t_data *data)
{
	if (philo->state != HAS_TWO_FORKS)
		return ;
	philo->last_meal = get_time(data);
	display_status(EATING, philo, data);
	usleep_in_ms(data->param[TIME_TO_EAT], data);
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	if (philo->state != EATING)
		return ;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display_status(SLEEPING, philo, data);
	usleep_in_ms(data->param[TIME_TO_SLEEP], data);
	display_status(THINKING, philo, data);
}
