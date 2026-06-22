/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/13 15:00:32 by username         #+#    #+#              */
/*   Updated: 2026/06/22 13:44:55 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config		*config;
	t_simulation	*sim;

	if (check_args(argc, argv) == -1)
		return (0);
	config = ft_init(argv);
	sim = init_simulation(config);
	if (!config || !sim)
	{
		printf("[ERROR]: field to allocation config");
		return (1);
	}
	return (0);
}
