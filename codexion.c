/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:00:32 by username          #+#    #+#             */
/*   Updated: 2026/06/28 14:51:59 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	start_simulation(t_simulation *sim)
{
	pthread_t	*thread_ids;
	pthread_t	monitor_id;
	int			i;

	i = 0;
	thread_ids = malloc(sizeof(pthread_t) * sim->config->number_of_coders);
	if (!thread_ids)
		return ;
	while (i < sim->config->number_of_coders)
	{
		pthread_create(&thread_ids[i], NULL, coder_routine, &sim->coders[i]);
		i++;
	}
	pthread_create(&monitor_id, NULL, monitor_routine, sim);
	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
	pthread_join(monitor_id, NULL);
	free(thread_ids);
}

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
	sim->config->start_time = get_current_time();
	start_simulation(sim);
	free(sim->coders);
	free(sim->dongles->heap);
	free(sim->dongles);
	free(sim->config);
	free(sim);
	return (0);
}
