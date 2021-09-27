/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/27 11:06:05 by EugenieFran      ###   ########.fr       */
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

int	live(t_philo *philo, t_data *data)
{
	int	exit_status;

	exit_status = FAIL;
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)data))
		return (exit_status);
	if (pthread_detach(philo->life_insurance))
		return (exit_status);
	while (not_enough_meals(philo, data) && !someone_died(philo, data))
	{
		philo_takes_forks(philo, data);
		philo_eats(philo, data);
		philo_sleeps_then_thinks(philo, data);
	}
	if (data->count_meals && philo->nb_of_meals == data->param[NB_OF_MEALS])
		exit_status = MEALS_REACHED;
	else if (data->philo_died == TRUE)
		exit_status = DEATH;
	return (exit_status);
}
