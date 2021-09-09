/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:07 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/08 12:32:10 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	usleep_in_ms(long int time_in_ms)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time < time_in_ms))
		usleep(10);
}

t_bool	time_is_valid(long int time)
{
	return (time >= 0 && time < 2147483648);
}

long int	get_time(void)
{
	struct timeval	timeval;
	long int		time_in_ms;

	gettimeofday(&timeval, NULL);
	time_in_ms = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (time_in_ms);
}
