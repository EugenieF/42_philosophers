/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 22:08:25 by EugenieFran      ###   ########.fr       */
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
	NO_NEED		= 0,
	NEEDED		= 1,
}		t_boolean;

typedef enum s_param
{
	NB_OF_PHILO		= 1,
	TIME_TO_DIE		= 2,
	TIME_TO_EAT		= 3,
	TIME_TO_SLEEP	= 4,
	NB_OF_MEALS		= 5,
}	t_param;

typedef enum s_status
{
	THINKING		= 0,
	HAS_A_FORK		= 1,
	SLEEPING		= 2,
	EATING			= 3,
	DEAD			= 4,
	HAS_TWO_FORKS	= 5,
}	t_status;

typedef struct s_philo
{
	int				num;
	long int		last_meal;
	int				nb_of_meals;
	int				state;			
	t_bool			done;
	pthread_t		life_thread;
	pthread_t		life_insurance;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				i;
	long int		start_time;
	t_bool			someone_died;
	int				count_meals;
	int				*param;
	t_philo			*philo;
	char			**status;
	pthread_mutex_t	writing_lock;
	pthread_mutex_t	count_meals_lock;
	pthread_mutex_t	check_death_lock;
	pthread_mutex_t	end_lock;
}					t_data;

#endif
