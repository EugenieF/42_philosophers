/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/27 19:32:01 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	someone_died(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	if (philo->state == DEAD || data->philo_died == TRUE)
		ret = TRUE;
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
