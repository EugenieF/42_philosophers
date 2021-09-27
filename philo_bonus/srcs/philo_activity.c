/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/27 19:12:31 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_takes_forks(t_philo *philo, t_data *data)
{
	sem_wait(philo->sem->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	if (data->param[NB_OF_PHILO] == 1)
	{
		smart_usleep_in_ms(data->param[TIME_TO_DIE], philo, data);
		return (FAIL);
	}
	if (someone_died(philo, data))
	{
		sem_post(data->sem->forks_lock);
		return (FAIL);
	}
	sem_wait(philo->sem->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	philo->state = HAS_TWO_FORKS;
	if (someone_died(philo, data))
	{
		sem_post(data->sem->forks_lock);
		sem_post(data->sem->forks_lock);
		return (FAIL);
	}
	return (SUCCESS);
}

void	philo_eats(t_philo *philo, t_data *data)
{
	if (philo->state != HAS_TWO_FORKS || data->philo_died == TRUE)
		return ;
	sem_wait(philo->sem->meal_lock);
	philo->last_meal = get_time();
	sem_post(philo->sem->meal_lock);
	display_status(EATING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_EAT], philo, data);
	philo->nb_of_meals++;
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	if (philo->state != EATING || data->philo_died == TRUE)
		return ;
	sem_post(philo->sem->forks_lock);
	sem_post(philo->sem->forks_lock);
	display_status(SLEEPING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_SLEEP], philo, data);
	if (!not_enough_meals(philo, data) || someone_died(philo, data))
		return ;
	display_status(THINKING, philo, data);
}
