/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:59:19 by username          #+#    #+#             */
/*   Updated: 2026/06/27 12:24:37 by hamezoua         ###   ########.fr       */
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

t_config	*ft_init(char **argv)
{
	t_config	*init;

	init = malloc(sizeof(t_config));
	if (!(init))
	{
		return (NULL);
	}
	init->number_of_coders = ft_atoi(argv[1]);
	init->time_to_burnout = ft_atoi(argv[2]);
	init->time_to_compile = ft_atoi(argv[3]);
	init->time_to_debug = ft_atoi(argv[4]);
	init->time_to_refactor = ft_atoi(argv[5]);
	init->number_of_compiles_required = ft_atoi(argv[6]);
	init->dongle_cooldown = ft_atoi(argv[7]);
	init->simulation_dead = 0;
	if (strcmp("fifo", argv[8]) == 0)
		init->scheduler = 1;
	else
	{
		init->scheduler = 0;
	}
	return (init);
}

int	check_args_numbers(int argc, char **argv, int i)
{
	if (argc != 9)
	{
		printf("[ERROR]: argument count = %d.\n", argc);
		printf("Please check, argument count must be 8.\n");
		return (-1);
	}
	if ((i == 1 || i == 2 || i == 6) && ft_atoi(argv[i]) <= 0)
	{
		printf("[ERROR]: please check ");
		printf("argument number of % d this value ", i);
		printf("%s it must be > 0 and < [INT_NAX] \n ", argv[i]);
		return (-1);
	}
	else if (ft_atoi(argv[i]) == -1)
	{
		printf("[ERROR]: please check this ");
		printf(" argument number of %d this value %s it ", i, argv[i]);
		printf("must be >= 0 and <= [INT_NAX] \n ");
		return (-1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < 9)
	{
		if (i == 8)
		{
			if ((strcmp("fifo", argv[i]) != 0) && (strcmp("edf", argv[i]) != 0))
			{
				printf("this argument %s must be fifo or edf exactly", argv[i]);
				return (-1);
			}
		}
		else
		{
			if (check_args_numbers(argc, argv, i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
