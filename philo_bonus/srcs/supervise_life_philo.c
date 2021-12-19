/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/19 11:49:08 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	meals_count_reached(t_philo *philo, t_data *data)
{
	int	ret;

	if (data->count_meals == NO_NEED)
		return (FALSE);
	ret = FALSE;
	sem_wait(philo->meal_lock);
	if (philo->nb_of_meals >= data->param[NB_OF_MEALS])
		ret = TRUE;
	sem_post(philo->meal_lock);
	return (ret);
}

t_bool	philo_died(t_philo *philo, t_data *data)
{
	int				ret;
	unsigned long	time_to_die;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	sem_wait(philo->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{
		display_status(DEAD, philo, data);
		sem_post(data->end_lock);
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
	philo = &data->philo[data->i];
	while (1)
	{
		if (meals_count_reached(philo, data)
			|| philo_died(philo, data))
			return (NULL);
		usleep(100);
	}
}
