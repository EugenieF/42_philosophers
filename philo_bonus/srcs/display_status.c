/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:04 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/10/09 16:50:27 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_status(int status, t_philo *philo, t_data *data)
{
	unsigned long	time_in_ms;

	sem_wait(philo->sem->writing_lock);
	if (data->philo_died || data->count_meals)
		return ;
	time_in_ms = get_time() - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %lu\t\tPhilo nᵒ %d %s\n",
		time_in_ms, philo->num, data->status[status]);
	philo->state = status;
	sem_post(philo->sem->writing_lock);
}
