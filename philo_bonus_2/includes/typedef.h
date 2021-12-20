/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:02:06 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/12/19 11:56:55 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

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

typedef int	t_bool;

typedef enum e_boolean
{
	CHILD			= 0,
	FAIL			= 0,
	SUCCESS			= 1,
	FALSE			= 0,
	TRUE			= 1,
	NO_NEED			= 0,
	NEEDED			= 1,
	DEATH			= 2,
	MEALS_REACHED	= 3,
}		t_boolean;

typedef struct s_philo
{
	int				num;
	unsigned long	last_meal;
	int				nb_of_meals;		
	t_bool			is_dead;
	pid_t			pid;
	pthread_t		life_insurance;
	sem_t			*meal_lock;
	char			*sem_name;
}					t_philo;

typedef struct s_data
{
	int				i;
	unsigned long	start_time;
	t_bool			meals_reached;
	int				count_meals;
	int				*param;
	char			**status;
	t_philo			*philo;
	sem_t			*writing_lock;
	sem_t			*end_lock;
	sem_t			*forks_lock;
}					t_data;

#endif