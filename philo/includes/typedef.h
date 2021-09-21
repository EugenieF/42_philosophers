/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/21 13:26:18 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef int	t_bool;

# ifdef __linux__
#  define IS_LINUX 1

typedef enum s_status
{
	THINKING		= 0,
	HAS_A_FORK		= 1,
	SLEEPING		= 2,
	EATING			= 3,
	DEAD			= 4,
	HAS_TWO_FORKS	= 5,
}	t_status;
# else
#  define IS_LINUX 0

typedef enum s_status
{
	THINKING		= 1,
	HAS_A_FORK		= 2,
	SLEEPING		= 3,
	EATING			= 4,
	DEAD			= 5,
	HAS_TWO_FORKS	= 6,
}	t_status;
# endif

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

typedef struct s_philo
{
	int				num;
	unsigned long	last_meal;
	int				nb_of_meals;
	int				state;			
	t_bool			done;
	pthread_t		life_thread;
	pthread_t		life_insurance;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	meal_lock;
}					t_philo;

typedef struct s_data
{
	int				i;
	unsigned long	start_time;
	t_bool			someone_died;
	int				count_meals;
	int				*param;
	t_philo			*philo;
	char			**status;
	pthread_mutex_t	writing_lock;
	pthread_mutex_t	count_meals_lock;
	pthread_mutex_t	data_lock;
}					t_data;

#endif
