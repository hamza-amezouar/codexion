/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:00:32 by username          #+#    #+#             */
/*   Updated: 2026/06/20 16:16:50 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == -1)
		return 0;
	t_config *config;
	t_simulation *sim;
	config = ft_init(argv);
	sim = init_simulation(config);
	if (!config || !sim)
	{
		printf("[ERROR]: field to allocation config");
		return(1);
	}
	sim->start_time = get_current_time();
	return 0;
}
