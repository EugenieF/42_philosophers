/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:36:15 by efrancon          #+#    #+#             */
/*   Updated: 2021/12/21 15:36:16 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handle_zero_meals(t_data *data)
{
	printf("\n  TIME IN MS\t  PHILO Nᵒ\tSTATE\n");
	printf("----------------------------------------------\n");
	printf("\n    All %d philosophers ", data->param[NB_OF_PHILO]);
	printf("ate their %d meals\n", data->param[NB_OF_MEALS]);
	printf("\n----------------------------------------------\n\n");
	cleanup(data);
	return (0);
}

void	exit_error_cleanup(char *message, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(" failed\n", 2);
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->param)
	{
		free(data->param);
		data->param = NULL;
	}
	free(data);
	data = NULL;
	exit(EXIT_FAILURE);
}

void	exit_error(char *message, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	cleanup(data);
	exit(EXIT_FAILURE);
}
