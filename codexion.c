/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:00:32 by username          #+#    #+#             */
/*   Updated: 2026/07/06 18:30:13 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coders_join(t_simulation *sim, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}

void	create_monitor(t_simulation *sim, int counter)
{
	pthread_t	monitor_id;

	if (pthread_create(&monitor_id, NULL, monitor_routine, sim) != 0)
	{
		printf("ERROR: failed to create monitor thread\n");
		pthread_mutex_lock(&sim->config->mutex_dead);
		sim->config->simulation_dead = 1;
		pthread_mutex_unlock(&sim->config->mutex_dead);
		coders_join(sim, counter);
		return ;
	}
	coders_join(sim, counter);
	pthread_join(monitor_id, NULL);
}

void	start_simulation(t_simulation *sim)
{
	int	counter;

	counter = 0;
	while (counter < sim->config->number_of_coders)
	{
		if (pthread_create(&sim->coders[counter].thread, NULL, coder_routine,
				&sim->coders[counter]) != 0)
			break ;
		counter++;
	}
	if (counter < sim->config->number_of_coders)
	{
		printf("ERROR: failed to create thread %d\n", counter + 1);
		pthread_mutex_lock(&sim->config->mutex_dead);
		sim->config->simulation_dead = 1;
		pthread_mutex_unlock(&sim->config->mutex_dead);
		coders_join(sim, counter);
		return ;
	}
	create_monitor(sim, counter);
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
	pthread_mutex_destroy(&sim->config->brodcast_mutex);
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
		printf("[ERROR]: field to allocation this number of coders %d",
			config->number_of_coders);
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
