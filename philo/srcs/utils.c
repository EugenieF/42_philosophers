/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:41:11 by efrancon          #+#    #+#             */
/*   Updated: 2021/09/20 15:05:10 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_mutex(pthread_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex));
}

int	unlock_mutex(pthread_mutex_t *mutex)
{
	return (pthread_mutex_unlock(mutex));
}

int	ft_atoi(const char *str)
{
	unsigned long	i;
	unsigned long	res;
	int				sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		s1_len;
	char	*copy;

	if (!s1)
		return (NULL);
	i = 0;
	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	copy = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
