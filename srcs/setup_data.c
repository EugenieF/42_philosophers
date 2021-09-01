/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:35 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/01 13:05:43 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	**create_status(void)
{
	char	**status;

	status = (char **)malloc(sizeof(char *) * 6);
	if (!status)
		return (NULL);
	status[THINKING] = "\033[38;5;123mis thinking\033[0m";
	status[HAS_A_FORK] = "\033[38;5;229mhas taken a fork\033[0m";
	status[EATING] = "\033[38;5;215mis eating\033[0m";
	status[SLEEPING] = "\033[38;5;32mis sleeping\033[0m";
	status[DEAD] = "\033[38;5;196mdied\033[0m";
	status[HAS_TWO_FORKS] = NULL;
	return (status);
}

void	set_to_null(t_data *data)
{
	data->param = NULL;
	data->status = NULL;
	data->philo = NULL;
}

t_data	*setup_data(int argc)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	set_to_null(data);
	data->start_time = get_time(data);
	argc--;
	data->param = (int *)malloc(sizeof(int) * argc);
	if (!data->param)
		return (NULL);
	data->status = create_status();
	if (!data->status)
		return (NULL);
	if (pthread_mutex_init(&data->writing_lock, NULL))
		return (NULL);
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (NULL);
	pthread_mutex_lock(&data->death_lock);
	if (pthread_mutex_init(&data->check_death, NULL))
		return (NULL);
	return (data);
}
