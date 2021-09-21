/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:31:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/21 13:23:30 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	someone_died(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	if (check_state_philo(DEAD, philo))
		return (TRUE);
	lock_mutex(&data->data_lock);
	if (data->someone_died == TRUE)
		ret = TRUE;
	unlock_mutex(&data->data_lock);
	return (ret);
}

t_bool	not_enough_meals(t_philo *philo, t_data *data)
{
	int	ret;

	ret = FALSE;
	lock_mutex(&data->count_meals_lock);
	if (data->count_meals == NO_NEED)
	{
		unlock_mutex(&data->count_meals_lock);
		return (TRUE);
	}
	unlock_mutex(&data->count_meals_lock);
	lock_mutex(&philo->meal_lock);
	if (philo->nb_of_meals < data->param[NB_OF_MEALS])
		ret = TRUE;
	unlock_mutex(&philo->meal_lock);
	return (ret);
}

t_bool	life_insurance(t_philo *philo, t_data *data)
{
	if (pthread_create(
			&philo->life_insurance, NULL, supervise_life_philo, (void *)data))
		return (FAIL);
	if (pthread_detach(philo->life_insurance))
		return (FAIL);
	return (SUCCESS);
}

void	*live(void *void_data)
{
	t_data		*data;
	t_philo		*philo;

	data = (t_data *)void_data;
	lock_mutex(&data->data_lock);
	philo = &data->philo[data->i];
	unlock_mutex(&data->data_lock);
	life_insurance(philo, data);
	if (philo->num % 2 == 0)
		smart_usleep_in_ms(data->param[TIME_TO_EAT], philo, data);
	while (not_enough_meals(philo, data) && !someone_died(philo, data))
	{
		philo_takes_forks(philo, data);
		if (someone_died(philo, data))
			break ;
		philo_eats(philo, data);
		philo_sleeps_then_thinks(philo, data);
	}
	return (NULL);
}
