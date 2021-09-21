/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:31 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/21 13:25:26 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	check_state_philo(int status, t_philo *philo)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&philo->state_lock);
	if (philo->state == status)
		ret = TRUE;
	unlock_mutex(&philo->state_lock);
	return (ret);
}

t_bool	philo_takes_forks(t_philo *philo, t_data *data)
{
	lock_mutex(&philo->left_fork);
	display_status(HAS_A_FORK, philo, data);
	if (!philo->right_fork)
	{
		smart_usleep_in_ms(data->param[TIME_TO_DIE], philo, data);
		unlock_mutex(&philo->left_fork);
		return (FAIL);
	}
	if (someone_died(philo, data))
	{
		unlock_mutex(&philo->left_fork);
		return (FAIL);
	}
	lock_mutex(philo->right_fork);
	display_status(HAS_A_FORK, philo, data);
	lock_mutex(&philo->state_lock);
	philo->state = HAS_TWO_FORKS;
	unlock_mutex(&philo->state_lock);
	if (someone_died(philo, data))
	{
		unlock_mutex(&philo->left_fork);
		unlock_mutex(philo->right_fork);
		return (FAIL);
	}
	return (SUCCESS);
}

void	philo_eats(t_philo *philo, t_data *data)
{
	lock_mutex(&philo->meal_lock);
	if (!check_state_philo(HAS_TWO_FORKS, philo))
	{
		unlock_mutex(&philo->meal_lock);
		return ;
	}
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	unlock_mutex(&philo->meal_lock);
	display_status(EATING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_EAT], philo, data);
}

void	philo_sleeps_then_thinks(t_philo *philo, t_data *data)
{
	if (!check_state_philo(EATING, philo))
		return ;
	unlock_mutex(&philo->left_fork);
	unlock_mutex(philo->right_fork);
	display_status(SLEEPING, philo, data);
	smart_usleep_in_ms(data->param[TIME_TO_SLEEP], philo, data);
	if (!not_enough_meals(philo, data))
		return ;
	display_status(THINKING, philo, data);
}
