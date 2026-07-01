/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 10:20:18 by username          #+#    #+#             */
/*   Updated: 2026/07/01 14:48:24 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_dongles(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->dongles = malloc(sizeof(t_dongle) * sim->config->number_of_coders);
	if (!sim->dongles)
		return (1);
	while (i < sim->config->number_of_coders)
	{
		sim->dongles[i].id_of_dongle = i + 1;
		sim->dongles[i].last_released_time = 0;
		sim->dongles[i].heap = malloc(sizeof(t_heap_node)
				* sim->config->number_of_coders);
		sim->dongles[i].heap_size = 0;
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
		pthread_cond_init(&sim->dongles[i].cond, NULL);
		i++;
	}
	return (0);
}

int	init_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->coders = malloc(sizeof(t_coder) * sim->config->number_of_coders);
	if (!sim->coders)
		return (1);
	while (i < sim->config->number_of_coders)
	{
		sim->coders[i].id_of_coder = i + 1;
		sim->coders[i].compile_count = 0;
		sim->coders[i].last_compile_start = get_current_time();
		sim->coders[i].config = sim->config;
		pthread_mutex_init(&sim->coders[i].mutex_time, NULL);
		sim->coders[i].left_dongle = &sim->dongles[i];
		sim->coders[i].right_dongle = &sim->dongles[(i + 1)
			% sim->config->number_of_coders];
		i++;
	}
	return (0);
}

t_simulation	*init_simulation(t_config *config)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	sim->config = config;
	pthread_mutex_init(&sim->config->mutex_dead, NULL);
	pthread_mutex_init(&sim->config->print_mutex, NULL);
	if (init_dongles(sim) != 0)
	{
		free(sim);
		return (NULL);
	}
	if (init_coders(sim) != 0)
	{
		free(sim->dongles);
		free(sim);
		return (NULL);
	}
	return (sim);
}

int	is_dead(t_config *config)
{
	int	is__dead;

	pthread_mutex_lock(&config->mutex_dead);
	is__dead = config->simulation_dead;
	pthread_mutex_unlock(&config->mutex_dead);
	return (is__dead);
}
