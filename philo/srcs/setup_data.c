/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:35 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/21 13:26:30 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	**create_status(void)
{
	char	**status;

	status = (char **)malloc(sizeof(char *) * 5);
	if (!status)
		return (NULL);
	status[THINKING] = ft_strdup("\033[38;5;123mis thinking\033[0m");
	if (!status[THINKING])
		return (NULL);
	status[HAS_A_FORK] = ft_strdup("\033[38;5;229mhas taken a fork\033[0m");
	if (!status[HAS_A_FORK])
		return (NULL);
	status[EATING] = ft_strdup("\033[38;5;215mis eating\033[0m");
	if (!status[EATING])
		return (NULL);
	status[SLEEPING] = ft_strdup("\033[38;5;32mis sleeping\033[0m");
	if (!status[SLEEPING])
		return (NULL);
	status[DEAD] = ft_strdup("\033[38;5;196mdied\033[0m");
	if (!status[DEAD])
		return (NULL);
	return (status);
}

t_bool	create_locks(t_data *data)
{
	if (pthread_mutex_init(&data->writing_lock, NULL))
		return (FAIL);
	if (pthread_mutex_init(&data->count_meals_lock, NULL))
		return (FAIL);
	if (pthread_mutex_init(&data->data_lock, NULL))
		return (FAIL);
	return (SUCCESS);
}

void	set_to_null(t_data *data)
{
	memset(data, 0, sizeof(t_data));
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
