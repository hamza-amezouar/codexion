/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:59:20 by hamezoua          #+#    #+#             */
/*   Updated: 2026/06/18 15:20:56 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
long get_current_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    long sec = time.tv_sec * 1000;
    long usec = time.tv_usec;
    printf("usc  %ld",usec);
    long millisecond = sec + usec;
    return millisecond;
}

void ft_usleep(long time_in_ms)
{
    long target_time = get_current_time() + time_in_ms;
    while (target_time > get_current_time())
    {
        usleep(1000);
    }
}
