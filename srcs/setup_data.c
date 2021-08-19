/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:35 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:18:23 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	**create_status(void)
{
	char	**status;

	status = (char **)malloc(sizeof(char *) * 5);
	if (!status)
		return (NULL);
	status[THINKING] = "\033[38;5;87mis thinking\033[0m";
	status[HAS_A_FORK] = "\033[38;5;226mhas taken a fork\033[0m";
	status[EATING] = "\033[38;5;82mis eating\033[0m";
	status[SLEEPING] = "\033[38;5;33mis sleeping\033[0m";
	status[DEAD] = "\033[38;5;196mdied\033[0m";
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
	int		ret;

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
	ret = pthread_mutex_init(&data->writing_lock, NULL);
	if (ret)
		return (NULL);
	return (data);
}
