/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:17:13 by username          #+#    #+#             */
/*   Updated: 2026/06/26 20:59:17 by hamezoua         ###   ########.fr       */
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

    if (coder->left_dongle->id_of_dongle < coder->right_dongle->id_of_dongle)
    {
        
        pthread_mutex_lock(&coder->left_dongle->mutex);
        pthread_mutex_lock(&coder->right_dongle->mutex);
    }
    else
    {
        pthread_mutex_lock(&coder->right_dongle->mutex);
        pthread_mutex_lock(&coder->left_dongle->mutex);
    }
    heap_insert(coder->left_dongle, coder->id_of_coder, priority);
    heap_insert(coder->right_dongle, coder->id_of_coder, priority);

    while (coder->left_dongle->heap[0].coder_id != coder->id_of_coder || coder->right_dongle->heap[0].coder_id != coder->id_of_coder)
    {
        if (coder->left_dongle->heap[0].coder_id != coder->id_of_coder)
        {
            pthread_mutex_unlock(&coder->right_dongle->mutex);
            pthread_cond_wait(&coder->left_dongle->cond, &coder->left_dongle->mutex);
            pthread_mutex_lock(&coder->right_dongle->mutex);
        }
        else if (coder->right_dongle->heap[0].coder_id != coder->id_of_coder)
        {
            pthread_mutex_unlock(&coder->left_dongle->mutex);
            pthread_cond_wait(&coder->right_dongle->cond, &coder->right_dongle->mutex);
            pthread_mutex_lock(&coder->left_dongle->mutex);
        }
        
    }
    heap_extract_min(coder->left_dongle);
    heap_extract_min(coder->right_dongle);
    pthread_mutex_unlock(&coder->left_dongle->mutex);
    pthread_mutex_unlock(&coder->right_dongle->mutex);
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