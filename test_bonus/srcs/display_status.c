/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:04 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/16 11:53:26 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_status(int status, t_philo *philo, t_data *data)
{
	unsigned long	time_in_ms;

	if (other_philo_died(data))
		return ;
	sem_wait(philo->sem->writing_lock);
	time_in_ms = get_time() - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %lu\t\t", time_in_ms);
	printf("Philo nᵒ %d %s\n", philo->num, data->status[status]);
	sem_post(philo->sem->writing_lock);
	sem_wait(philo->state_lock);
	philo->state = status;
	sem_post(philo->state_lock);
}

t_bool	death_already_displayed(t_data *data)
{
	int	ret;

	sem_wait(data->sem->data_lock);
	if (data->someone_died == TRUE)
		ret = TRUE;
	else
	{
		data->someone_died = TRUE;
		ret = FALSE;
	}
	sem_post(data->sem->data_lock);
	return (ret);
}

void	display_death(t_philo *philo, t_data *data)
{
	unsigned long	time_in_ms;

	if (death_already_displayed(data))
		return ;
	sem_wait(data->sem->writing_lock);
	time_in_ms = get_time() - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	printf("  %lu\t\t", time_in_ms);
	printf("Philo nᵒ %d %s\n", philo->num, data->status[DEAD]);
	sem_post(data->sem->writing_lock);
	sem_wait(philo->state_lock);
	philo->state = DEAD;
	sem_post(philo->state_lock);
}
