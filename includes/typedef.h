/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/01 16:11:28 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef int	t_bool;

typedef enum e_boolean
{
	FAIL		= 0,
	SUCCESS		= 1,
	FALSE		= 0,
	TRUE		= 1,
}		t_boolean;

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
	THINKING		= 1,
	HAS_A_FORK		= 2,
	SLEEPING		= 3,
	EATING			= 4,
	DEAD			= 5,
	HAS_TWO_FORKS	= 6,
}	t_status;

typedef struct s_philo
{
	int				num;
	long int		last_meal;
	int				state;			
	pthread_t		life_thread;
	pthread_t		check_death_thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				i;
	long int		start_time;
	t_bool			someone_died;
	int				*param;
	t_philo			*philo;
	char			**status;
	pthread_mutex_t	writing_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	check_death;
}			t_data;

#endif
