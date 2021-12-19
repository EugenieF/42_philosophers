/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:41:11 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/17 11:18:33 by efrancon         ###   ########.fr       */
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
