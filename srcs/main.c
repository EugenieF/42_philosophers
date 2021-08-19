/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:25 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:21:39 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_leaks(void)
{
	system("leaks philo");
}

int	exit_program(char *message, int exit_code, t_data *data)
{
	cleanup(data);
	printf("%s\n", message);
	atexit(check_leaks);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = setup_data(argc);
	if (!data)
		return (1);
	if (!(argc == 5 || argc == 6) || !fill_and_check_parameters(argv, data))
		return (exit_program("Error: invalid arguments\n", 0, data));
	printf("\n");
	if (!init_philo(data) || !run_philo(data))
		return (exit_program("Error: philo failed\n", EXIT_FAILURE, data));
	cleanup(data);
	printf("\n");
	atexit(check_leaks);
	return (0);
}
