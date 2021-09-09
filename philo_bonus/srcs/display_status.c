/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:04 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/08 19:46:56 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_status(int status, t_philo *philo, t_data *data)
{
	long int	time_in_ms;

	if (data->philo_died == FALSE && data->meals_reached == FALSE)
		sem_wait(philo->writing_lock);
	else
		return ;
	time_in_ms = get_time() - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %ld\t\t", time_in_ms);
	printf("Philo nᵒ %d %s\n", philo->num, data->status[status]);
	philo->state = status;
	if (status != DEAD)
		sem_post(philo->writing_lock);
}
