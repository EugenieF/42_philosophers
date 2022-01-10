/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/10 16:16:23 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	is_dead(t_philo *philo)
{
	int	ret;

	ret = FALSE;
	sem_wait(philo->end_lock);
	if (philo->is_dead)
		ret = TRUE;
	sem_post(philo->end_lock);
	return (ret);
}

t_bool	must_stop(t_philo *philo, t_data *data)
{
	int	ret;

	(void)data;
	ret = FALSE;
	sem_wait(philo->end_lock);
	if (philo->end)
		ret = TRUE;
	sem_post(philo->end_lock);
	return (ret);
}

static void	life_insurance(t_philo *philo, t_data *data)
{
	sem_unlink(philo->sem_meal_name);
	sem_unlink(philo->sem_end_name);
	open_semaphore(&philo->meal_lock, philo->sem_meal_name, 1, data);
	open_semaphore(&philo->end_lock, philo->sem_end_name, 1, data);
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)philo))
		exit_error("pthread_create() failed", data);
	if (data->param[NB_OF_PHILO] == 1)
		return ;
	if (data->param[NB_OF_PHILO] % 2 != 0
		&& philo->num == data->param[NB_OF_PHILO])
		smart_usleep_in_ms(data->param[TIME_TO_EAT] * 2, philo);
	else if ((data->param[NB_OF_PHILO] % 2 == 0
			&& philo->num > data->param[NB_OF_PHILO] / 2)
		|| (data->param[NB_OF_PHILO] % 2 != 0
			&& philo->num > (data->param[NB_OF_PHILO] - 1) / 2))
		smart_usleep_in_ms(data->param[TIME_TO_EAT], philo);
}

void	live(t_philo *philo, t_data *data)
{
	int		exit_status;
	void	*ret_thread;

	exit_status = MEALS_REACHED;
	life_insurance(philo, data);
	while (!must_stop(philo, data))
	{
		if (!philo_takes_forks(philo, data))
			break ;
		philo_eats(philo, data);
		philo_sleeps_then_thinks(philo, data);
	}
	if (pthread_join(philo->life_insurance, &ret_thread))
		exit_error("pthread_detach() failed", data);
	if (!ret_thread)
	{
		display_death(philo, data);
		exit_status = DEATH;
	}
	if (sem_close(philo->meal_lock))
		exit_error("sem_close() failed", data);
	if (sem_close(philo->end_lock))
		exit_error("sem_close() failed", data);
	cleanup(data);
	exit(exit_status);
}
