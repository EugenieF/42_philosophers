/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:25 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/28 23:01:00 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_leaks(void)
{
	system("leaks philo_bonus");
}

int	exit_program(char *message, int exit_code, t_data *data)
{
	printf("%s\n", message);
	if (!cleanup(data))
		printf("Error: close_semaphores() failed\n");
	atexit(check_leaks);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = setup_data(argc);
	if (!data)
	{
		printf("Error: setup_data() failed\n");
		return (1);
	}
	if (!(argc == 5 || argc == 6) || !fill_and_check_parameters(argv, data))
		return (exit_program("Error: invalid arguments", 1, data));
	printf("\n");
	if (!init_philo(data) || !run_philo(data))
		return (exit_program("Error: philo failed", 1, data));
	printf("----------------------------------------------\n\n");
	if (!cleanup(data))
	{
		printf("Error: close_semaphores() failed\n");
		return (1);
	}
//	atexit(check_leaks);
	return (0);
}
