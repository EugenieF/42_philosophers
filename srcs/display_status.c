/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:04 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 14:04:08 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_status(int status, t_philo *philo, t_data *data)
{
	long int	time_in_ms;

	if (data->someone_died == FALSE)
		pthread_mutex_lock(&data->writing_lock);
	if (data->someone_died == TRUE)
		return ;
	time_in_ms = get_time(data) - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %ld\t\t", time_in_ms);
	printf("Philo nᵒ %d %s\n", philo->num, data->status[status]);
	philo->state = status;
	pthread_mutex_unlock(&data->writing_lock);
}
