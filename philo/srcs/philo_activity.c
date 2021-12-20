/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/20 12:06:02 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	philo_takes_forks(t_philo *philo, t_data *data)
{
	lock_mutex(philo->main_fork);
	display_status(HAS_A_FORK, philo, data);
	if (!philo->minor_fork)
	{
		smart_usleep_in_ms(data->param[TIME_TO_DIE], data);
		unlock_mutex(philo->main_fork);
		return (FAIL);
	}
	// if (someone_died(data))
	// {
	// 	unlock_mutex(philo->main_fork);
	// 	return (FAIL);
	// }
	lock_mutex(philo->minor_fork);
	display_status(HAS_A_FORK, philo, data);
	if (someone_died(data))
	{
		unlock_mutex(philo->main_fork);
		unlock_mutex(philo->minor_fork);
		return (FAIL);
	}
	return (SUCCESS);
}

void	philo_eats(t_philo *philo, t_data *data)
{
	lock_mutex(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	// printf("\nPHILO n˚%d : MEALS = %d\n", philo->num, philo->nb_of_meals);
	unlock_mutex(&philo->meal_lock);
	display_status(EATING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_EAT], data);
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	unlock_mutex(philo->main_fork);
	unlock_mutex(philo->minor_fork);
	display_status(SLEEPING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_SLEEP], data);
	if (had_enough_meals(data))
		return ;
	display_status(THINKING, philo, data);
}
