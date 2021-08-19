/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:30:19 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/08/19 22:21:32 by EugenieFran      ###   ########.fr       */
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
t_data		*setup_data(int argc);
t_bool		fill_and_check_parameters(char **argv, t_data *data);
t_bool		init_philo(t_data *data);
t_bool		run_philo(t_data *data);
t_bool		create_thread(t_data *data);
void		takes_forks(t_philo *philo, t_data *data);
void		eats(t_philo *philo, t_data *data);
void		releases_forks_and_sleeps(t_philo *philo, t_data *data);
void		thinks(t_philo *philo, t_data *data);
void		display_status(int status, t_philo *philo, t_data *data);
long int	get_time(t_data *data);
t_bool		time_is_valid(long int time);
void		cleanup(t_data *data);
int			exit_program(char *message, int exit_code, t_data *data);

#endif
