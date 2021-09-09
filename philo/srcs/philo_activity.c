/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 20:17:03 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_takes_forks(t_philo *philo, t_data *data)
{
	if (philo->state == THINKING && pthread_mutex_lock(&philo->left_fork) == 0)
		display_status(HAS_A_FORK, philo, data);
	if (!philo->right_fork)
		return (usleep_in_ms(data->param[TIME_TO_DIE]));
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
	philo->last_meal = get_time();
	display_status(EATING, philo, data);
	usleep_in_ms(data->param[TIME_TO_EAT]);
	philo->nb_of_meals++;
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	if (philo->state != EATING)
		return ;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display_status(SLEEPING, philo, data);
	usleep_in_ms(data->param[TIME_TO_SLEEP]);
	display_status(THINKING, philo, data);
}
