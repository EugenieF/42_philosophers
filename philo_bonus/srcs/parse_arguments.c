/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 19:29:00 by EugenieFr         #+#    #+#             */
/*   Updated: 2021/09/27 10:32:44 by EugenieFran      ###   ########.fr       */
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

t_bool	argv_is_valid(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!char_is_valid(argv[i]))
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
	if (IS_LINUX)
		j = 0;
	else
		j = 1;
	nb = 0;
	while (argv[++i])
	{
		if (!argv_is_valid(argv[i]))
			return (FAIL);
		nb = ft_atoi(argv[i]);
		if (!number_is_valid(nb))
			return (FAIL);
		data->param[j++] = (int)nb;
	}
	if (i == 6)
		data->count_meals = NEEDED;
	return (SUCCESS);
}
