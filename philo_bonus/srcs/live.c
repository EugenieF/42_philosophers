/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/15 14:34:12 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	someone_died(t_philo *philo, t_data *data)
{
	int				ret;
	unsigned long	time_to_die;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	if (philo->state == DEAD || data->philo_died == TRUE)
		ret = TRUE;
	sem_wait(philo->sem->meal_lock);
	if (time_to_die < get_time() - philo->last_meal)
	{
		sem_post(philo->sem->meal_lock);
		display_status(DEAD, philo, data);
		data->philo_died = TRUE;
		philo->state = DEAD;
		sem_post(philo->sem->end_lock);
		ret = TRUE;
		return (ret);
	}
	sem_post(philo->sem->meal_lock);
	return (ret);
}

t_bool	not_enough_meals(t_philo *philo, t_data *data)
{
	int	ret;

	ret = TRUE;
	if (data->count_meals == NO_NEED)
		return (ret);
	if (philo->nb_of_meals >= data->param[NB_OF_MEALS])
		ret = FALSE;
	return (ret);
}

static void	life_insurance(t_philo *philo, t_data *data)
{
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)data))
		exit_error("pthread_create()", data);
	if (pthread_detach(philo->life_insurance))
		exit_error("pthread_detach()", data);
}

int	live(t_philo *philo, t_data *data)
{
	int	exit_status;

	exit_status = FAIL;
	life_insurance(philo, data);
	while (not_enough_meals(philo, data) && !someone_died(philo, data))
	{
		if (!philo_takes_forks(philo, data))
			break ;
		philo_eats(philo, data);
		if (someone_died(philo, data))
		{
			sem_post(data->sem->forks_lock);
			sem_post(data->sem->forks_lock);
			break ;
		}
		philo_sleeps_then_thinks(philo, data);
	}
	if (data->count_meals && philo->nb_of_meals == data->param[NB_OF_MEALS])
		exit_status = MEALS_REACHED;
	else if (data->philo_died == TRUE)
		exit_status = DEATH;
	return (exit_status);
}
