/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:01:30 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/07 12:41:14 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_skip_whitespaces(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		s;
	long	res;

	s = 1;
	res = 0;
	i = ft_skip_whitespaces(str, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (INT_MAX - (str[i] - '0')) / 10)
		{
			if (s == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

static int	not_num(char **str)
{
	int	i;
	int	j;

	j = 1;
	while (str[j])
	{
		i = 0;
		if (str[j][0] == '\0' || !str[j])
			return (2);
		while (str[j][i])
		{
			if (str[j][0] == '0')
				return (1);
			if (str[j][i] < '0' || str[j][i] > '9')
				return (2);
			i++;
		}
		if ((ft_atoi(str[j]) > INT_MAX) || (ft_atoi(str[j]) < INT_MIN))
			return (2);
		j++;
	}
	return (0);
}

int	check_error(int argc, char *argv[])
{
	if (argc < 5)
		return (printf("Error. Need to have at least 4 parameters\n"));
	if (argc > 6)
		return (printf("Error. Need to have at maximum 5 parameters\n"));
	if (ft_atoi(argv[1]) > 200)
		return (printf("Error. Maximum 200 philosophers\n"));
	if (not_num(argv) == 1)
		return (printf("Error. 0 not acceptable\n"));
	if (not_num(argv) == 2)
		return (printf("Error. All parameters should be valid numbers\n"));
	return (0);
}
