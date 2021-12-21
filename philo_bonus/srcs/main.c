/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:25 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/21 12:04:12 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	main(int argc, char **argv)
{
	t_data	*data;

	data = setup_data(argc);
	if (!(argc == 5 || argc == 6) || !fill_and_check_parameters(argv, data))
		exit_error("invalid arguments", data);
	init_philo(data);
	printf("\n");
	run_philo(data);
	printf("----------------------------------------------\n\n");
	cleanup(data);
	return (0);
}
