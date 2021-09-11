/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:30:19 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/09 20:19:28 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "typedef.h"

int			ft_atoi(const char *str);
char		*ft_strdup(const char *s1);
long int	get_time(void);
void		usleep_in_ms(long int time_in_ms);
t_bool		time_is_valid(long int time);
t_data		*setup_data(int argc);
void		unlink_semaphores(void);
t_bool		fill_and_check_parameters(char **argv, t_data *data);
t_bool		init_philo(t_data *data);
t_bool		run_philo(t_data *data);
int			live(t_philo *philo, t_data *data);
void		philo_takes_forks(t_philo *philo, t_data *data);
void		philo_eats(t_philo *philo, t_data *data);
void		philo_sleeps_then_thinks(t_philo *philo, t_data *data);
void		display_status(int status, t_philo *philo, t_data *data);
void		*supervise_life_philo(void *void_data);
t_bool		cleanup(t_data *data);
int			exit_program(char *message, int exit_code, t_data *data);

#endif
