/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/04 16:19:13 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	someone_died(t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->data_lock);
	if (data->someone_died == TRUE)
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}

t_bool	had_enough_meals(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&philo->meal_lock);
	if (data->need_count_meals
		&& philo->nb_of_meals >= data->param[NB_OF_MEALS])
		ret = TRUE;
	unlock_mutex(&philo->meal_lock);
	return (ret);
}

static void	life_insurance(t_philo *philo, t_data *data)
{
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)philo))
		exit_error("pthread_create() failed", data);
	int ret = pthread_detach(philo->life_insurance);
	if (ret)
	{
		printf("ret = %d\n", ret);
		exit_error("pthread_detach() failed", data);
	}
}

void	*live(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	lock_mutex(&data->data_lock);
	philo = &data->philo[data->i];
	unlock_mutex(&data->data_lock);
	life_insurance(philo, data);
	if (philo->num % 2 == 0)
		smart_usleep_in_ms(data->param[TIME_TO_EAT], data);
	while (!had_enough_meals(philo, data) && !someone_died(data))
	{
		if (!philo_takes_forks(philo, data))
			break ;
		philo_eats(philo, data);
		if (someone_died(data))
		{
			unlock_mutex(philo->main_fork);
			unlock_mutex(philo->minor_fork);
			break ;
		}
		philo_sleeps_then_thinks(philo, data);
	}
	// if (pthread_join(philo->life_insurance, NULL))
	// 	exit_error("pthread_join() failed", data);
	return (NULL);
}
