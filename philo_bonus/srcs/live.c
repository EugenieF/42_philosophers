/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/07 21:57:05 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	had_enough_meals(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	sem_wait(philo->meal_lock);
	if (data->count_meals == NEEDED
		&& philo->nb_of_meals >= data->param[NB_OF_MEALS])
		ret = TRUE;
	sem_post(philo->meal_lock);
	return (ret);
}

static void	life_insurance(t_philo *philo, t_data *data)
{
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)philo))
		exit_error("pthread_create() failed", data);
	if (pthread_detach(philo->life_insurance))
		exit_error("pthread_detach() failed", data);
}

void	live(t_philo *philo, t_data *data)
{
	sem_unlink(philo->sem_name);
	open_semaphore(&philo->meal_lock, philo->sem_name, 1, data);
	life_insurance(philo, data);
	while (!had_enough_meals(philo, data))
	{
		philo_takes_forks(philo, data);
		philo_eats(philo, data);
		philo_sleeps_then_thinks(philo, data);
	}
	exit(MEALS_REACHED);
}
