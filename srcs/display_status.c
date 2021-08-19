/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:04 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:22:47 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_status(int status, t_philo *philo, t_data *data)
{
	long int	time_in_ms;

	pthread_mutex_lock(&data->writing_lock);
	time_in_ms = get_time(data) - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("%ld ms\t\t", time_in_ms);
	printf("Philo nᵒ %d %s\n", philo->num, data->status[status]);
	pthread_mutex_unlock(&data->writing_lock);
}
