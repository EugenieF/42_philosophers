/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:29:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/02 13:07:38 by EugenieFran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	number_is_valid(long nb)
{
	return (nb > 0 && nb < 2147483648);
}

t_bool	char_is_valid(char c)
{
	return ((c >= '0' && c <= '9') || (c == '-' || c == '+')
		|| (c >= 9 && c <= 13));
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

t_bool	argv_is_valid(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!char_is_valid(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

t_bool	fill_and_check_parameters(char **argv, t_data *data)
{
	int		i;
	long	nb;

	i = 1;
	nb = 0;
	while (argv[i])
	{
		if (!argv_is_valid(argv[i]))
			return (FAIL);
		nb = ft_atoi(argv[i]);
		if (!number_is_valid(nb))
			return (FAIL);
		data->param[i++] = (int)nb;
	}
	if (i == 6)
		data->count_meals = NEEDED;
	return (SUCCESS);
}
