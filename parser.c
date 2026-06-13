/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parser.c                                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/13 14:59:19 by username         #+#    #+#              */
/*   Updated: 2026/06/13 18:21:44 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_atoi(char *str)
{
	int		i;
	long	result;
	long	sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] && str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (((result * sign) > 2147483647) || ((result * sign) < -2147483648))
			return (-1);
		i++;
	}
	if (!(str[i] >= '0' || str[i] <= '9') || (result * sign) < 0)
		return (-1);
	return (result * sign);
}

int	check_args(int argc, char **argv)
{
	if (argc != 9)
		return (-1);
	if (ft_atoi(argv[1]) == -1)
		return (-1);
	if (ft_atoi(argv[2]) == -1)
		return (-1);
	if (ft_atoi(argv[3]) == -1)
		return (-1);
	if (ft_atoi(argv[4]) == -1)
		return (-1);
	if (ft_atoi(argv[5]) == -1)
		return (-1);
	if (ft_atoi(argv[6]) == -1)
		return (-1);
	if (ft_atoi(argv[7]) == -1)
		return (-1);
	if ((strcmp(argv[8], "fifo") != 0) && (strcmp(argv[8], "edf") != 0))
		return (-1);
	return (0);
}
