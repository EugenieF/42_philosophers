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

t_bool	nobody_is_dead(t_philo *philo, t_data *data)
{
	int	ret;

	ret = TRUE;
	if (philo->state == DEAD || data->philo_died == TRUE)
		ret = FALSE;
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
	pthread_detach(philo->life_insurance);
	while (not_enough_meals(philo, data) && nobody_is_dead(philo, data))
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
