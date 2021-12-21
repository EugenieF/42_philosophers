/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:28:25 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/21 15:27:44 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = setup_data(argc);
	if (!(argc == 5 || argc == 6) || !fill_and_check_parameters(argv, data))
		exit_error("invalid arguments", data);
	if (data->need_count_meals && !data->param[NB_OF_MEALS])
		return (handle_zero_meals(data));
	init_philo(data);
	printf("\n");
	run_philo(data);
	printf("----------------------------------------------\n\n");
	cleanup(data);
	return (0);
}
