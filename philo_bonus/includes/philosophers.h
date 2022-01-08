/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:30:19 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/08 15:29:01 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include "typedef.h"

/***   LIBFT   ***/

int				ft_isdigit(char c);
int				ft_isspace(char c);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(int count, int size);
void			clean_free(char **str);
long			ft_atoi(const char *str);
char			*ft_strdup(const char *s1);
int				ft_strlen(const char *s);
void			*ft_memset(void *b, int c, int len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin_and_free(char *s1, char *s2);
char			*ft_itoa(int n);

/***   UTILS   ***/

int				handle_zero_meals(t_data *data);
void			exit_error(char *message, t_data *data);
void			exit_error_cleanup(char *message, t_data *data);

/***   TIME   ***/

unsigned long	get_time(void);
void			usleep_in_ms(unsigned long time_in_ms);
t_bool			time_is_valid(unsigned long time);

/***   INIT   ***/

t_data			*setup_data(int argc);
t_bool			fill_and_check_parameters(char **argv, t_data *data);
void			init_philo(t_data *data);
void			open_semaphore(sem_t **semaphore, char *name,
					int nb_of_resources, t_data *data);

/***   PHILO   ***/

void			run_philo(t_data *data);
void			live(t_philo *philo, t_data *data);
t_bool			philo_takes_forks(t_philo *philo, t_data *data);
void			philo_eats(t_philo *philo, t_data *data);
void			philo_sleeps_then_thinks(t_philo *philo, t_data *data);

/***  MONITORING  ***/

void			display_status(int status, t_philo *philo, t_data *data);
void			*supervise_life_philo(void *void_data);
t_bool			philo_is_dead(t_philo *philo);
t_bool			had_enough_meals(t_philo *philo, t_data *data);

/***   CLEAN   ***/

void			cleanup(t_data *data);
void			free_philo(t_data *data);
void			free_status(t_data *data);
t_bool			close_semaphores(t_data *data);
void			unlink_semaphores(void);
void			cleanup_fork(t_philo *philo, t_data *data);
void			cleanup_fork_meal(t_data *data);

#endif
