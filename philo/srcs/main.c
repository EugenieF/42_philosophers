/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:25 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/19 11:27:01 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_leaks(void)
{
	system("leaks philo");
}

void	exit_error(char *message, t_data *data)
{
	char	*error_message;

	error_message = ft_strjoin("Error: ", message);
	error_message = ft_strjoin_and_free(error_message, "\n");
	ft_putstr_fd(error_message, 2);
	clean_free(&error_message);
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
	// atexit(check_leaks);
	return (0);
}
