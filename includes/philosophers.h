/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:30:19 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 13:20:56 by EugenieFran      ###   ########.fr       */
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
# include "typedef.h"

long int	get_time(t_data *data);
void		usleep_in_ms(useconds_t time_in_ms, t_data *data);
t_bool		time_is_valid(long int time);
t_data		*setup_data(int argc);
t_bool		fill_and_check_parameters(char **argv, t_data *data);
t_bool		init_philo(t_data *data);
t_bool		run_philo(t_data *data);
void		*live(void *void_data);
void		philo_takes_forks(t_philo *philo, t_data *data);
void		philo_eats(t_philo *philo, t_data *data);
void		philo_sleeps_then_thinks(t_philo *philo, t_data *data);
void		display_status(int status, t_philo *philo, t_data *data);
void		*supervise_life_philo(void *void_data);
void		cleanup(t_data *data);
int			exit_program(char *message, int exit_code, t_data *data);

#endif
