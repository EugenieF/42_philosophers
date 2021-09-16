/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/08 20:53:42 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_takes_forks(t_philo *philo, t_data *data)
{
	if (philo->state == THINKING)
	{
		sem_wait(philo->forks_lock);
		display_status(HAS_A_FORK, philo, data);
	}
	if (data->param[NB_OF_PHILO] == 1)
		return (usleep_in_ms(data->param[TIME_TO_DIE]));
	if (philo->state == HAS_A_FORK)
	{
		sem_wait(philo->forks_lock);
		display_status(HAS_A_FORK, philo, data);
		philo->state = HAS_TWO_FORKS;
	}
}

void	philo_eats(t_philo *philo, t_data *data)
{
	sem_wait(philo->check_death_lock);
	if (philo->state != HAS_TWO_FORKS || data->philo_died == TRUE)
	{
		sem_post(philo->check_death_lock);
		return ;
	}
	philo->last_meal = get_time();
	sem_post(philo->check_death_lock);
	display_status(EATING, philo, data);
	usleep_in_ms(data->param[TIME_TO_EAT]);
	philo->nb_of_meals++;
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	if (philo->state != EATING || data->philo_died == TRUE)
		return ;
	sem_post(philo->forks_lock);
	sem_post(philo->forks_lock);
	display_status(SLEEPING, philo, data);
	usleep_in_ms(data->param[TIME_TO_SLEEP]);
	display_status(THINKING, philo, data);
}
