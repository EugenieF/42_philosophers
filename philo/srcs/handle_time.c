/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:07 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/12 20:50:53 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	time_is_valid(unsigned long time)
{
	return (time < 2147483648);
}

unsigned long	get_time(void)
{
	struct timeval	timeval;
	unsigned long	time_in_ms;

	gettimeofday(&timeval, NULL);
	time_in_ms = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (time_in_ms);
}

void	usleep_in_ms(unsigned long time_in_ms)
{
	unsigned long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_in_ms)
		usleep(100);
}

void	smart_usleep_in_ms(int time, t_data *data)
{
	unsigned long	start_time;
	unsigned long	time_in_ms;

	start_time = get_time();
	time_in_ms = (unsigned long)time;
	if (time < 499)
		usleep_in_ms(time_in_ms);
	else
	{
		while (get_time() - start_time < time_in_ms)
		{
			if (is_dead(data))
				break ;
			usleep(500);
		}
	}
}
