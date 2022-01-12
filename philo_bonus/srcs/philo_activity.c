/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/12 22:42:16 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_takes_forks(t_philo *philo, t_data *data)
{
	sem_wait(data->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	if (data->param[NB_OF_PHILO] == 1)
	{
		usleep_in_ms(data->param[TIME_TO_DIE]);
		return (FAIL);
	}
	if (must_stop(philo, data))
	{
		sem_post(data->forks_lock);
		return (FAIL);
	}
	sem_wait(data->forks_lock);
	display_status(HAS_A_FORK, philo, data);
	if (must_stop(philo, data))
	{
		sem_post(data->forks_lock);
		sem_post(data->forks_lock);
		return (FAIL);
	}
	return (SUCCESS);
}

void	philo_eats(t_philo *philo, t_data *data)
{
	if (must_stop(philo, data))
		return ;
	sem_wait(philo->meal_lock);
	philo->last_meal = get_time();
	display_status(EATING, philo, data);
	sem_post(philo->meal_lock);
	smart_usleep_in_ms(data->param[TIME_TO_EAT], philo);
	sem_wait(philo->meal_lock);
	philo->nb_of_meals++;
	sem_post(philo->meal_lock);
	sem_post(data->forks_lock);
	sem_post(data->forks_lock);
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	display_status(SLEEPING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_SLEEP], philo);
	if (must_stop(philo, data))
		return ;
	display_status(THINKING, philo, data);
	sem_wait(philo->meal_lock);
	if (!data->is_even && (philo->num + philo->nb_of_meals)
		% data->simultaneous_meals != 1 && data->simultaneous_meals != 1)
	{
		sem_post(philo->meal_lock);
		return ;
	}
	// printf("philo %d | nb_of_meals = %d\n", philo->num, philo->nb_of_meals);
	sem_post(philo->meal_lock);
	smart_usleep_in_ms(data->param[TIME_TO_THINK], philo);
}
