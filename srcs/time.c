/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <efrancon@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:25 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/18 22:01:27 by EugenieFr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

/*
void	clean_usleep(long int time_in_ms)
{

}
*/
