/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/17 11:39:22 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# define CHILD	0

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

typedef enum s_param
{
	NB_OF_PHILO		= 0,
	TIME_TO_DIE		= 1,
	TIME_TO_EAT		= 2,
	TIME_TO_SLEEP	= 3,
	NB_OF_MEALS		= 4,
}	t_param;
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

typedef enum s_param
{
	NB_OF_PHILO		= 1,
	TIME_TO_DIE		= 2,
	TIME_TO_EAT		= 3,
	TIME_TO_SLEEP	= 4,
	NB_OF_MEALS		= 5,
}	t_param;
# endif

typedef int	t_bool;

typedef enum e_boolean
{
	FAIL			= 0,
	SUCCESS			= 1,
	FALSE			= 0,
	TRUE			= 1,
	NO_NEED			= 0,
	NEEDED			= 1,
	DEATH			= 2,
	MEALS_REACHED	= 3,
}		t_boolean;

typedef struct s_semaphores
{
	sem_t	*forks_lock;
	sem_t	*writing_lock;
	sem_t	*end_lock;
	sem_t	*check_death_lock;
}		t_semaphores;

typedef struct s_philo
{
	int				num;
	unsigned long	last_meal;
	int				nb_of_meals;
	int				state;			
	pid_t			pid;
	pthread_t		life_insurance;
	t_semaphores	*sem;
}					t_philo;

typedef struct s_data
{
	int				i;
	unsigned long	start_time;
	t_bool			philo_died;
	t_bool			meals_reached;
	int				count_meals;
	int				*param;
	char			**status;
	t_philo			*philo;
	t_semaphores	*sem;
}					t_data;

#endif
