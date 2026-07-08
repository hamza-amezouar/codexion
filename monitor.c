/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 16:15:20 by username          #+#    #+#             */
/*   Updated: 2026/07/08 11:44:43 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	handle_burnout(t_simulation *sim, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&sim->config->mutex_dead);
	sim->config->simulation_dead = 1;
	pthread_mutex_unlock(&sim->config->mutex_dead);
	pthread_mutex_lock(&sim->coders[i].config->print_mutex);
	printf("%ld %d burned out\n", get_current_time()
		- sim->coders->config->start_time, sim->coders[i].id_of_coder);
	pthread_mutex_unlock(&sim->coders[i].config->print_mutex);
	while (j < sim->config->number_of_coders)
	{
		pthread_mutex_unlock(&sim->coders[i].mutex_time);
		pthread_mutex_lock(&sim->dongles[j].mutex);
		pthread_cond_broadcast(&sim->dongles[j].cond);
		pthread_mutex_unlock(&sim->dongles[j].mutex);
		pthread_mutex_lock(&sim->coders[i].mutex_time);
		j++;
	}
	pthread_mutex_unlock(&sim->coders[i].mutex_time);
	return (1);
}

int	controler_coders(t_simulation *sim, int *all_done)
{
	int		i;
	long	last_compile;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex_time);
		last_compile = get_current_time() - sim->coders[i].last_compile_start;
		if (last_compile >= sim->config->time_to_burnout)
			return (handle_burnout(sim, i));
		if (sim->coders[i].compile_count \
			< sim->config->number_of_compiles_required)
			*all_done = 0;
		pthread_mutex_unlock(&sim->coders[i].mutex_time);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				all_done;
	int				flage;

	sim = (t_simulation *)arg;
	while (1)
	{
		if (is_dead(sim->config) == 1)
			break ;
		all_done = 1;
		flage = controler_coders(sim, &all_done);
		if (flage == 1)
			return (NULL);
		if (all_done)
		{
			pthread_mutex_lock(&sim->config->mutex_dead);
			sim->config->simulation_dead = 1;
			pthread_mutex_unlock(&sim->config->mutex_dead);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
