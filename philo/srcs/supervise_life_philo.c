/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/20 12:35:00 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	meals_count_reached(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->data_lock);
	if (!data->need_count_meals)
	{
		unlock_mutex(&data->data_lock);
		return (FALSE);
	}
	lock_mutex(&philo->meal_lock);
	if (!philo->done
		&& philo->nb_of_meals >= data->param[NB_OF_MEALS])
	{
		data->count_meals++;
		philo->done = TRUE;
		// printf("\ncount meals = %d\n", data->count_meals);
	}
	unlock_mutex(&philo->meal_lock);
	if (data->count_meals >= data->param[NB_OF_PHILO])
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}

t_bool	philo_died(t_philo *philo, t_data *data)
{
	unsigned long	time_to_die;

	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	if (someone_died(data))
		return (TRUE);
	lock_mutex(&philo->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{
		unlock_mutex(&philo->meal_lock);
		display_death(philo, data);
		return (TRUE);
	}
	unlock_mutex(&philo->meal_lock);
	return (FALSE);
}

void	*supervise_life_philo(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	lock_mutex(&data->data_lock);
	philo = &data->philo[data->i];
	// printf("\nSupervise --> PHILO N˚%d | data->i = %d\n", philo->num, data->i);
	unlock_mutex(&data->data_lock);
	while (1)
	{
		if (meals_count_reached(philo, data)
			|| philo_died(philo, data))
		{
			lock_mutex(&data->data_lock);
			data->finish++;
			unlock_mutex(&data->data_lock);
			return (NULL);
		}
		usleep(100);
	}
}
