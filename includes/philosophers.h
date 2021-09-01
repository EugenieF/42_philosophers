/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:30:19 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/01 16:24:55 by EugenieFran      ###   ########.fr       */
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

int			ft_strlen(const char *str);
int			ft_atoi(const char *str);
void		usleep_in_ms(useconds_t time_in_ms, t_data *data);
t_data		*setup_data(int argc);
t_bool		fill_and_check_parameters(char **argv, t_data *data);
t_bool		init_philo(t_data *data);
t_bool		run_philo(t_data *data);
t_bool		create_thread(t_data *data);
void		philo_takes_forks(t_philo *philo, t_data *data);
void		philo_eats(t_philo *philo, t_data *data);
void		philo_sleeps_then_thinks(t_philo *philo, t_data *data);
void		display_status(int status, t_philo *philo, t_data *data);
long int	get_time(t_data *data);
t_bool		time_is_valid(long int time);
void		*check_death_philo(void *void_data);
void		end_philo_thread(t_data *data);
void		cleanup(t_data *data);
int			exit_program(char *message, int exit_code, t_data *data);

#endif
