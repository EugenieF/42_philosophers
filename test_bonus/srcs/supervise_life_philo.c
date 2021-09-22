/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/17 11:45:11 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	meals_count_reached(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	sem_wait(data->sem->data_lock);
	if (data->count_meals == NO_NEED)
	{
		sem_post(data->sem->data_lock);
		return (FALSE);
	}
	sem_post(data->sem->data_lock);
	sem_wait(philo->meal_lock);
	if (philo->nb_of_meals >= data->param[NB_OF_MEALS])
	{
		data->meals_reached = TRUE;
		ret = TRUE;
	}
	sem_post(philo->meal_lock);
	return (FALSE);
}

t_bool	philo_died(t_philo *philo, t_data *data)
{
	int				ret;
	unsigned long	time_to_die;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	if (someone_died(philo, data))
		return (TRUE);
	sem_wait(philo->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{

		display_death(philo, data);
		sem_post(philo->sem->end_lock);
		ret = TRUE;
	}
	sem_post(philo->meal_lock);
	return (ret);
}

void	*supervise_life_philo(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	sem_wait(data->sem->data_lock);
	philo = &data->philo[data->i];
	sem_post(data->sem->data_lock);
	while (1)
	{
		if (meals_count_reached(philo, data))
			return (NULL);
		if (philo_died(philo, data))
			return (NULL);
		usleep(10);
	}
}
