/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 16:15:20 by username          #+#    #+#             */
/*   Updated: 2026/06/29 14:58:11 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				i;
	int				j;
	long			last_compile;
    int all_done;
    
	sim = (t_simulation *) arg;
	while (1)
	{
        if (is_dead(sim->config) == 1)
            break ;
        all_done = 1;
		i = 0;
		while (i < sim->config->number_of_coders)
		{
			pthread_mutex_lock(&sim->coders[i].mutex_time);
			last_compile = get_current_time() - sim->coders[i].last_compile_start;
			if (last_compile >= sim->config->time_to_burnout)
			{
				j = 0;
				pthread_mutex_lock(&sim->config->mutex_dead);
				sim->config->simulation_dead = 1;
				pthread_mutex_unlock(&sim->config->mutex_dead);
				printf("%ld %d burned out\n", get_current_time() - sim->coders->config->start_time, sim->coders[i].id_of_coder);
				while (j < sim->config->number_of_coders)
				{
					pthread_cond_broadcast(&sim->dongles[j].cond);
					j++;
				}
				pthread_mutex_unlock(&sim->coders[i].mutex_time);
				return (NULL);
			}
			if (sim->coders[i].compile_count < sim->config->number_of_compiles_required)
                all_done = 0;
			pthread_mutex_unlock(&sim->coders[i].mutex_time);
			i++;
		}
		if (all_done)
		{
			pthread_mutex_lock(&sim->config->mutex_dead);
			sim->config->simulation_dead = 1;
			pthread_mutex_unlock(&sim->config->mutex_dead);
            return NULL;
		}
		usleep(1000);
	}
	return (NULL);
}
