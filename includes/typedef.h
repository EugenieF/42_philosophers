/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:06:39 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# define FAIL 		0
# define SUCCESS	1

typedef int	t_bool;

typedef enum s_param
{
	NB_OF_PHILO					= 1,
	TIME_TO_DIE					= 2,
	TIME_TO_EAT					= 3,
	TIME_TO_SLEEP				= 4,
	TIMES_EACH_PHILO_MUST_EAT	= 5,
}	t_param;

typedef enum s_status
{
	THINKING	= 0,
	HAS_A_FORK	= 1,
	SLEEPING	= 2,
	EATING		= 3,
	DEAD		= 4,
}	t_status;

typedef struct s_philo
{
	int				num;
	long int		last_meal;
	pthread_t		thread;
	pthread_t		check_death;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				i;
	long int		start_time;
	t_bool			is_even;
	int				*param;
	t_philo			*philo;
	char			**status;
	pthread_mutex_t	writing_lock;
}			t_data;

#endif
