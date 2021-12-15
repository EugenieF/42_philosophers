/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:04 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/15 15:21:27 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*get_message(
	unsigned long time_in_ms, int status, t_philo *philo, t_data *data)
{
	char			*time_str;
	char			*philo_num;
	char			*message;

	time_str = ft_itoa(time_in_ms);
	philo_num = ft_itoa(philo->num);
	message = ft_strjoin("  ", time_str);
	clean_free(&time_str);
	message = ft_strjoin_and_free(message, "\t\t");
	message = ft_strjoin_and_free(message, "Philo nᵒ ");
	message = ft_strjoin_and_free(message, philo_num);
	clean_free(&philo_num);
	message = ft_strjoin_and_free(message, " ");
	message = ft_strjoin_and_free(message, data->status[status]);
	message = ft_strjoin_and_free(message, "\n");
	return (message);
}

void	display_status(int status, t_philo *philo, t_data *data)
{
	unsigned long	time_in_ms;
	char			*message;

	time_in_ms = get_time() - data->start_time;
	if (!time_is_valid(time_in_ms))
		return ;
	message = get_message(time_in_ms, status, philo, data);
	if (data->philo_died == FALSE && data->meals_reached == FALSE)
		sem_wait(philo->sem->writing_lock);
	else
		return ;
	philo->state = status;
	clean_free(&message);
	if (status != DEAD)
		sem_post(philo->sem->writing_lock);
}
