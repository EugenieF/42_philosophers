/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:29:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2022/01/10 18:04:55 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

t_bool	number_is_valid(long nb, int i)
{
	if (i == 5)
		return (nb >= 0 && nb < 2147483648);
	return (nb > 0 && nb < 2147483648);
}

t_bool	argv_is_valid(char *argv)
{
	int	i;

	i = 0;
	while (ft_isspace(argv[i]))
		i++;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	fill_and_check_parameters(char **argv, t_data *data)
{
	int		i;
	int		j;
	long	nb;

	i = 0;
	j = 0;
	nb = 0;
	while (argv[++i])
	{
		if (!argv_is_valid(argv[i]))
			return (FAIL);
		nb = ft_atoi(argv[i]);
		if (!number_is_valid(nb, i))
			return (FAIL);
		data->param[j++] = (int)nb;
	}
	if (i == 6)
		data->count_meals = NEEDED;
	if (data->param[NB_OF_PHILO] % 2 == 0)
		data->is_even = TRUE;
	return (SUCCESS);
}
