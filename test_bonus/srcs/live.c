/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/09 11:55:21 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	other_philo_died(t_data *data)
{
	int	ret;

	ret = FALSE;
	sem_wait(data->sem->data_lock);
	if (data->someone_died == TRUE)
		ret = TRUE;
	sem_post(data->sem->data_lock);
	return (ret);
}

t_bool	someone_died(t_philo *philo, t_data *data)
{
	if (check_state_philo(DEAD, philo))
		return (TRUE);
	if (other_philo_died(data))
		return (TRUE);
	return (FALSE);
}

t_bool	not_enough_meals(t_philo *philo, t_data *data)
{
	int	ret;

	ret = TRUE;
	sem_wait(data->sem->data_lock);
	if (data->count_meals == NO_NEED)
	{
		sem_post(data->sem->data_lock);
		return (ret);
	}
	sem_post(data->sem->data_lock);
	sem_wait(philo->meal_lock);
	if (philo->nb_of_meals >= data->param[NB_OF_MEALS])
		ret = FALSE;
	sem_post(philo->meal_lock);
	return (ret);
}

t_bool	life_insurance(t_philo *philo, t_data *data)
{
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)data))
		return (FAIL);
	if (pthread_detach(philo->life_insurance))
		return (FAIL);
	return (SUCCESS);
}

int	live(t_philo *philo, t_data *data)
{
	int	exit_status;

	exit_status = FAIL;
	if (!life_insurance(philo, data))
		return (exit_status);
	while (not_enough_meals(philo, data) && !someone_died(philo, data))
	{
		if (!philo_takes_forks(philo, data))
			break ;
		philo_eats(philo, data);
		if (someone_died(philo, data))
		{
			sem_post(philo->sem->forks_lock);
			sem_post(philo->sem->forks_lock);
			break ;
		}
		philo_sleeps_then_thinks(philo, data);
	}
	if (!not_enough_meals(philo, data))
		exit_status = MEALS_REACHED;
	else if (someone_died(philo, data))
		exit_status = DEATH;
	return (exit_status);
}
