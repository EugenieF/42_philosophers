/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:35 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/19 11:30:59 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*safe_strdup(const char *s1, t_data *data)
{
	int		i;
	int		s1_len;
	char	*copy;

	if (!s1)
		return (NULL);
	i = 0;
	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	copy = (char *)ft_calloc(1, sizeof(char) * (s1_len + 1));
	if (!copy)
		exit_error("malloc() failed", data);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	create_status(t_data *data)
{
	data->status = (char **)ft_calloc(1, sizeof(char *) * 6);
	if (!data->status)
		exit_error("malloc() failed", data);
	data->status[THINKING] = safe_strdup(
			"\033[38;5;123mis thinking\033[0m", data);
	data->status[HAS_A_FORK] = safe_strdup(
			"\033[38;5;229mhas taken a fork\033[0m", data);
	data->status[SLEEPING] = safe_strdup("\033[38;5;32mis sleeping\033[0m", data);
	data->status[EATING] = safe_strdup("\033[38;5;215mis eating\033[0m", data);
	data->status[DEAD] = safe_strdup("\033[38;5;196mdied\033[0m", data);
	data->status[5] = NULL;
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

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_error("malloc() failed", data);
	set_to_null(data);
	argc--;
	data->param = (int *)ft_calloc(1, sizeof(int) * argc);
	if (!data->param)
		exit_error("malloc() failed", data);
	create_status(data);
	return (data);
}
