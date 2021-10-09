/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_life_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:30:52 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/10/09 16:52:52 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	meals_count_reached(t_philo *philo, t_data *data)
{
	if (data->count_meals == NO_NEED)
		return (FALSE);
	if (philo->nb_of_meals >= data->param[NB_OF_MEALS])
	{
		data->meals_reached = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void	display_death(unsigned long time, t_philo *philo, t_data *data)
{
	unsigned long	time_in_ms;

	sem_wait(philo->sem->writing_death_lock);
	time_in_ms = time - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %lu\t\tPhilo nᵒ %d %s\n",
		time_in_ms, philo->num, data->status[DEAD]);
	data->philo_died = TRUE;
	philo->state = DEAD;
	sem_post(philo->sem->end_lock);
	sem_wait(philo->sem->writing_lock);
}

t_bool	philo_died(t_philo *philo, t_data *data)
{
	int				ret;
	unsigned long	time_to_die;
	unsigned long	actual_time;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	sem_wait(philo->sem->meal_lock);
	actual_time = get_time();
	if (time_to_die < actual_time - philo->last_meal)
	{
		sem_post(philo->sem->meal_lock);
		display_death(actual_time, philo, data);
		return (TRUE);
	}
	sem_post(philo->sem->meal_lock);
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
		if ((data->count_meals && meals_count_reached(philo, data))
			|| philo_died(philo, data))
			return (NULL);
		usleep(10);
	}
}
