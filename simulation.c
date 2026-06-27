/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:17:13 by username          #+#    #+#             */
/*   Updated: 2026/06/27 18:19:43 by hamezoua         ###   ########.fr       */
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

    while ((coder->left_dongle->heap[0].coder_id != coder->id_of_coder ||
        coder->right_dongle->heap[0].coder_id != coder->id_of_coder) && is_dead(config) != 1)
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
}

void    drop_dongles(t_coder *coder)
{
    heap_extract_min(coder->left_dongle);
    heap_extract_min(coder->right_dongle);
    pthread_cond_broadcast(&coder->left_dongle->cond);
    pthread_cond_broadcast(&coder->right_dongle->cond);
    pthread_mutex_unlock(&coder->left_dongle->mutex);
    pthread_mutex_unlock(&coder->right_dongle->mutex);
}
int is_dead(t_config *config)
{
    int is__dead;
    pthread_mutex_lock(&config->mutex_dead);
    is__dead = config->simulation_dead;
    pthread_mutex_unlock(&config->mutex_dead);
    return (is__dead);
}
void *coder_routine(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    while (1)
    {
        if (is_dead(coder->config) == 1)
            break;
        take_dongles(coder, coder->config);

        if (is_dead(coder->config) == 1)
        {
            drop_dongles(coder);
            break;
        }
        pthread_mutex_lock(&coder->config->print_mutex);
        if (is_dead(coder->config) == 0)
        {
            printf("%ld %d has taken a dongle\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
            if (is_dead(coder->config) == 0)
                printf("%ld %d has taken a dongle\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
            if (is_dead(coder->config) == 0)
                printf("%ld %d is compiling\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
        }
        pthread_mutex_unlock(&coder->config->print_mutex);

        pthread_mutex_lock(&coder->mutex_time);
        coder->last_compile_start = get_current_time();
        pthread_mutex_unlock(&coder->mutex_time);
        
        ft_usleep(coder->config->time_to_compile, coder);
        coder->compile_count++;
        drop_dongles(coder);
        
        pthread_mutex_lock(&coder->config->print_mutex);
        if (is_dead(coder->config) == 0)
            printf("%ld %d is debugging\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
        pthread_mutex_unlock(&coder->config->print_mutex);
        ft_usleep(coder->config->time_to_debug, coder);

        pthread_mutex_lock(&coder->config->print_mutex);
        if (is_dead(coder->config) == 0)
            printf("%ld %d is refactoring\n",get_current_time() - coder->config->start_time, coder->id_of_coder);
        pthread_mutex_unlock(&coder->config->print_mutex);
        ft_usleep(coder->config->time_to_refactor, coder);
    }
    
    return NULL;
}