/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:41:11 by efrancon          #+#    #+#             */
/*   Updated: 2022/01/04 14:46:00 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error_cleanup(char *message, t_data *data)
{
	ft_putstr_fd("\nError: ", 2);
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
	char	*error_message;

	error_message = ft_strjoin("\nError: ", message);
	error_message = ft_strjoin_and_free(error_message, "\n");
	lock_mutex(&data->writing_lock);
	ft_putstr_fd(error_message, 2);
	unlock_mutex(&data->writing_lock);
	clean_free(&error_message);
	cleanup(data);
	exit(EXIT_FAILURE);
}

int	lock_mutex(pthread_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex));
}

int	unlock_mutex(pthread_mutex_t *mutex)
{
	return (pthread_mutex_unlock(mutex));
}

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
