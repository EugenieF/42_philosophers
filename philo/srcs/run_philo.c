/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:13 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/07 17:43:42 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	philo_had_enough_meals(int i, t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->philo[i].meal_lock);
	if (data->need_count_meals && !data->philo[i].done
		&& data->philo[i].nb_of_meals >= data->param[NB_OF_MEALS])
	{
		ret = TRUE;
		data->philo[i].done = TRUE;
	}
	unlock_mutex(&data->philo[i].meal_lock);
	return (ret);
}

static t_bool	philo_died(int i, t_data *data)
{
	int				ret;
	unsigned long	time_to_die;

	ret = FALSE;
	time_to_die = (unsigned long)data->param[TIME_TO_DIE];
	lock_mutex(&data->philo[i].meal_lock);
	if (time_to_die < get_time() - data->philo[i].last_meal)
		ret = TRUE;
	unlock_mutex(&data->philo[i].meal_lock);
	return (ret);
}

static void	wait_loop(t_data *data)
{
	int				i;

	i = 0;
	while (1)
	{
		if (philo_died(i, data))
		{
			display_death(&data->philo[i], data);
			break ;
		}
		if (philo_had_enough_meals(i, data))
			data->count_meals++;
		if (data->count_meals >= data->param[NB_OF_PHILO])
		{
			lock_mutex(&data->data_lock);
			data->end = TRUE;
			unlock_mutex(&data->data_lock);
			break ;
		}
		i++;
		i = i % data->param[NB_OF_PHILO];
	}
}

static void	end_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->param[NB_OF_PHILO])
	{
		if (pthread_join(data->philo[i].life_thread, NULL))
			exit_error("pthread_join() failed", data);
	}
	if (data->need_count_meals && data->count_meals >= data->param[NB_OF_PHILO])
	{
		printf("\n    All %d philosophers ", data->param[NB_OF_PHILO]);
		printf("ate their %d meals\n", data->param[NB_OF_MEALS]);
	}
}

void	run_philo(t_data *data)
{
	int	i;

	i = 0;
	printf("  TIME IN MS\t  PHILO Nᵒ\tSTATE\n");
	printf("----------------------------------------------\n");
	while (i < data->param[NB_OF_PHILO])
	{
		if (pthread_create(&data->philo[i].life_thread,
				NULL, live, (void *)&data->philo[i]))
			exit_error("pthread_create() failed", data);
		usleep(100);
		i++;
	}
	wait_loop(data);
	end_philo(data);
}
