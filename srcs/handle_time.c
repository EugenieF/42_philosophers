/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:25 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/31 20:57:03 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	usleep_in_ms(useconds_t time_in_ms, t_data *data)
{
	long int	start_time;

	start_time = get_time(data);
	while ((get_time(data) - start_time < time_in_ms))
		usleep(time_in_ms / 100);
}

t_bool	time_is_valid(long int time)
{
	return (time >= 0 && time < 2147483648);
}

long int	get_time(t_data *data)
{
	struct timeval	timeval;
	long int		time_in_ms;
	int				ret;

	ret = gettimeofday(&timeval, NULL);
	if (ret != 0)
		exit_program("Error : gettimeofday failed\n", EXIT_FAILURE, data);
	time_in_ms = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (time_in_ms);
}
