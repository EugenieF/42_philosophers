/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:04 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/10/09 16:54:09 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_status(int status, t_philo *philo, t_data *data)
{
	unsigned long	time_in_ms;

	if (other_philo_died(data))
		return ;
	lock_mutex(&data->writing_lock);
	time_in_ms = get_time() - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %lu\t\tPhilo nᵒ %d %s\n",
		time_in_ms, philo->num, data->status[status]);
	unlock_mutex(&data->writing_lock);
	lock_mutex(&philo->state_lock);
	philo->state = status;
	unlock_mutex(&philo->state_lock);
}

t_bool	death_already_displayed(t_data *data)
{
	int	ret;

	lock_mutex(&data->data_lock);
	if (data->someone_died == TRUE)
		ret = TRUE;
	else
	{
		data->someone_died = TRUE;
		ret = FALSE;
	}
	unlock_mutex(&data->data_lock);
	return (ret);
}

void	display_death(t_philo *philo, t_data *data)
{
	unsigned long	time_in_ms;

	if (death_already_displayed(data))
		return ;
	lock_mutex(&data->writing_lock);
	time_in_ms = get_time() - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %lu\t\tPhilo nᵒ %d %s\n",
		time_in_ms, philo->num, data->status[DEAD]);
	unlock_mutex(&data->writing_lock);
	lock_mutex(&philo->state_lock);
	philo->state = DEAD;
	unlock_mutex(&philo->state_lock);
}
