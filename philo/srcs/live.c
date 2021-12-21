/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/21 11:28:46 by efrancon         ###   ########.fr       */
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

t_bool	had_enough_meals(t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->data_lock);
	if (data->need_count_meals && data->count_meals >= data->param[NB_OF_PHILO])
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}

static void	life_insurance(t_philo *philo, t_data *data)
{
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)data))
		exit_error("pthread_create() failed", data);
	if (pthread_detach(philo->life_insurance))
		exit_error("pthread_detach() failed", data);
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
	while (!had_enough_meals(data) && !someone_died(data))
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
	return (NULL);
}
