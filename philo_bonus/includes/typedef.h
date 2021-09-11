/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/11 12:23:40 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# define CHILD	0

# ifdef __linux__
#  define IS_LINUX 1
# else
#  define IS_LINUX 0
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
	pid_t			pid;
	pthread_t		life_insurance;
	sem_t			*forks_lock;
	sem_t			*writing_lock;
	sem_t			*end_lock;
}					t_philo;

typedef struct s_data
{
	int			i;
	long int	start_time;
	t_bool		philo_died;
	t_bool		meals_reached;
	int			count_meals;
	int			*param;
	t_philo		*philo;
	char		**status;
	sem_t		*forks_lock;
	sem_t		*writing_lock;
	sem_t		*end_lock;
}				t_data;

#endif
