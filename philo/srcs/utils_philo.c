/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:41:11 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/16 12:21:10 by efrancon         ###   ########.fr       */
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
