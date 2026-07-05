/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:00:32 by username          #+#    #+#             */
/*   Updated: 2026/07/05 15:17:59 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	start_simulation(t_simulation *sim)
{
	pthread_t	monitor_id;
	int			i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_create(&sim->coders[i].thread, \
			NULL, coder_routine, &sim->coders[i]);
		i++;
	}
	pthread_create(&monitor_id, NULL, monitor_routine, sim);
	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_id, NULL);
}

void	destroy_mutex(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		pthread_mutex_destroy(&sim->coders[i].mutex_time);
		free(sim->dongles[i].heap);
		i++;
	}
	pthread_mutex_destroy(&sim->config->mutex_dead);
	pthread_mutex_destroy(&sim->config->print_mutex);
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
	destroy_mutex(sim);
	free(sim->coders);
	free(sim->dongles);
	free(sim->config);
	free(sim);
	return (0);
}
