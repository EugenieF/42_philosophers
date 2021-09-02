/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:35 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 12:07:06 by EugenieFran      ###   ########.fr       */
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

t_bool	create_locks(t_data *data)
{
	if (pthread_mutex_init(&data->writing_lock, NULL))
		return (FAIL);
	if (pthread_mutex_init(&data->check_death_lock, NULL))
		return (FAIL);
	if (pthread_mutex_init(&data->count_meals_lock, NULL))
		return (FAIL);
	if (pthread_mutex_init(&data->end_lock, NULL))
		return (FAIL);
	pthread_mutex_lock(&data->end_lock);
	return (SUCCESS);
}

void	set_to_null(t_data *data)
{
	data->param = NULL;
	data->status = NULL;
	data->philo = NULL;
	data->count_meals = NO_NEED;
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
	if (!create_locks(data))
		return (NULL);
	return (data);
}
