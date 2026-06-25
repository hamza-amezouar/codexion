/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:17:13 by username          #+#    #+#             */
/*   Updated: 2026/06/25 18:25:51 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    take_dongles(t_coder *coder, t_config *config)
{
    long priority;
    
    if (coder->config->scheduler == 1)
        priority = get_current_time();
    else
        priority = coder->config->time_to_burnout + coder->last_compile_start;

    pthread_mutex_lock(&coder->left_dongle->mutex);
    pthread_mutex_lock(&coder->right_dongle->mutex);
    heap_insert(coder->left_dongle, coder->id_of_coder, priority);
    heap_insert(coder->right_dongle, coder->id_of_coder, priority);
}
void *coder_routine(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    while (1)
    {
        if (coder->config->simulation_dead == 1)
            break;
        take_dongles(coder, coder->config);
        coder->last_compile_start = get_current_time();
        ft_usleep(coder->config->time_to_compile, coder);
        coder->compile_count++;
        drop_dongles(coder, coder->config);
        ft_usleep(coder->config->time_to_debug, coder);
        ft_usleep(coder->config->time_to_refactor, coder);
    }
    
}
3277