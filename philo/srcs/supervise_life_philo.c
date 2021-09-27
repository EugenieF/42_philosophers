/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/27 19:01:18 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	meals_count_reached(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->count_meals_lock);
	if (data->count_meals == NO_NEED)
	{
		unlock_mutex(&data->count_meals_lock);
		return (FALSE);
	}
	lock_mutex(&philo->meal_lock);
	if (!philo->done && data->count_meals <= data->param[NB_OF_PHILO]
		&& philo->nb_of_meals == data->param[NB_OF_MEALS])
	{
		lock_mutex(&data->data_lock);
		data->count_meals++;
		unlock_mutex(&data->data_lock);
		philo->done = 1;
	}
	unlock_mutex(&philo->meal_lock);
	if (philo->done && data->count_meals > data->param[NB_OF_PHILO])
		ret = TRUE;
	unlock_mutex(&data->count_meals_lock);
	return (ret);
}

t_bool	philo_died(t_philo *philo, t_data *data)
{
	int				ret;
	unsigned long	time_to_die;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	if (someone_died(philo, data))
		return (TRUE);
	lock_mutex(&philo->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{
		display_death(philo, data);
		ret = TRUE;
	}
	unlock_mutex(&philo->meal_lock);
	return (ret);
}

void	*supervise_life_philo(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	lock_mutex(&data->data_lock);
	philo = &data->philo[data->i];
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
		usleep(10);
	}
}
