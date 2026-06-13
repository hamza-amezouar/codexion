/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:19 by username          #+#    #+#             */
/*   Updated: 2026/06/13 20:29:13 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (result > 2147483647)
			return (-1);
		i++;
	}
	if (!str[i])
		return (result);
	return (-1);
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
