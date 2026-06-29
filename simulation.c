/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:17:13 by username          #+#    #+#             */
/*   Updated: 2026/06/29 10:55:16 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void *coder_routine(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    while (1)
    {
        if (is_dead(coder->config) == 1)
            break;
        if (coder->config->number_of_coders == 1)
        {
            pthread_mutex_lock(&coder->left_dongle->mutex);
            printf("%ld %d has taken a dongle\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
            pthread_mutex_unlock(&coder->left_dongle->mutex);
            ft_usleep(coder->config->time_to_burnout + 20, coder);
            break;
            
        }
        take_dongles(coder, coder->config);
        pthread_mutex_lock(&coder->config->print_mutex);
        if (is_dead(coder->config) == 0)
            printf("%ld %d has taken a dongle\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
        if (is_dead(coder->config) == 0)
            printf("%ld %d has taken a dongle\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
        if (is_dead(coder->config) == 0)
            printf("%ld %d is compiling\n", get_current_time() - coder->config->start_time, coder->id_of_coder);
        pthread_mutex_unlock(&coder->config->print_mutex);
        if (is_dead(coder->config) == 1)
        {
            drop_dongles(coder);
            break;
        }
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