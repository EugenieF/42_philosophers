/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/07 16:57:39 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	must_stop(t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->data_lock);
	if (data->end == TRUE)
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}

void	*live(void *void_philo)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)void_philo;
	data = philo->data;
	if (philo->num % 2 == 0)
		smart_usleep_in_ms(data->param[TIME_TO_EAT], data);
	while (!must_stop(data))
	{
		if (!philo_takes_forks(philo, data))
			break ;
		philo_eats(philo, data);
		if (must_stop(data))
		{
			unlock_mutex(philo->main_fork);
			unlock_mutex(philo->minor_fork);
			break ;
		}
		philo_sleeps_then_thinks(philo, data);
	}
	return (NULL);
}
