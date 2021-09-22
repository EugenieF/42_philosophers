/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/17 11:55:12 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	check_state_philo(int status, t_philo *philo)
{
	int	ret;

	ret = FALSE;
	sem_wait(philo->state_lock);
	if (philo->state == status)
		ret = TRUE;
	sem_post(philo->state_lock);
	return (ret);
}

t_bool	philo_takes_forks(t_philo *philo, t_data *data)
{
	sem_wait(philo->sem->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	if (data->param[NB_OF_PHILO] == 1)
	{
		smart_usleep_in_ms(data->param[TIME_TO_DIE], philo, data);
		sem_post(philo->sem->forks_lock);
		return (FAIL);
	}
	if (someone_died(philo, data))
	{
		sem_post(philo->sem->forks_lock);
		return (FAIL);
	}
	sem_wait(philo->sem->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	sem_wait(philo->state_lock);
	philo->state = HAS_TWO_FORKS;
	sem_post(philo->state_lock);
	if (someone_died(philo, data))
	{
		sem_post(philo->sem->forks_lock);
		sem_post(philo->sem->forks_lock);
		return (FAIL);
	}
	return (SUCCESS);
}

void	philo_eats(t_philo *philo, t_data *data)
{
	sem_wait(philo->meal_lock);
	if (!check_state_philo(HAS_TWO_FORKS, philo))
	{
		sem_post(philo->meal_lock);
		return ;
	}
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	sem_post(philo->meal_lock);
	display_status(EATING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_EAT], philo, data);
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	if (!check_state_philo(EATING, philo))
		return ;
	sem_post(philo->sem->forks_lock);
	sem_post(philo->sem->forks_lock);
	display_status(SLEEPING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_SLEEP], philo, data);
	if (!not_enough_meals(philo, data))
		return ;
	display_status(THINKING, philo, data);
}
