/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:41:11 by efrancon          #+#    #+#             */
/*   Updated: 2021/09/21 22:35:30 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_mutex(pthread_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex));
}

int	unlock_mutex(pthread_mutex_t *mutex)
{
	return (pthread_mutex_unlock(mutex));
}

t_bool	check_state_philo(int status, t_philo *philo)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&philo->state_lock);
	if (philo->state == status)
		ret = TRUE;
	unlock_mutex(&philo->state_lock);
	return (ret);
}

t_bool	other_philo_died(t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->data_lock);
	if (data->someone_died == TRUE)
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}
