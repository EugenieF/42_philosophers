/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/20 10:29:39 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef int	t_bool;

typedef enum s_status
{
	THINKING		= 0,
	HAS_A_FORK		= 1,
	SLEEPING		= 2,
	EATING			= 3,
	DEAD			= 4,
	HAS_TWO_FORKS	= 5,
}	t_status;

typedef enum s_param
{
	NB_OF_PHILO		= 0,
	TIME_TO_DIE		= 1,
	TIME_TO_EAT		= 2,
	TIME_TO_SLEEP	= 3,
	NB_OF_MEALS		= 4,
}	t_param;

typedef enum e_boolean
{
	FAIL		= 0,
	SUCCESS		= 1,
	FALSE		= 0,
	TRUE		= 1,
}		t_boolean;

typedef struct s_philo
{
	int				num;
	unsigned long	last_meal;
	int				nb_of_meals;
	t_bool			done;
	pthread_t		life_thread;
	pthread_t		life_insurance;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*main_fork;
	pthread_mutex_t	*minor_fork;
	pthread_mutex_t	meal_lock;
}					t_philo;

typedef struct s_data
{
	int				i;
	unsigned long	start_time;
	t_bool			someone_died;
	t_bool			need_count_meals;
	int				count_meals;
	int				*param;
	t_philo			*philo;
	char			**status;
	pthread_mutex_t	writing_lock;
	pthread_mutex_t	data_lock;
	int				finish;
}					t_data;

#endif