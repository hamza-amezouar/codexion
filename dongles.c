/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:08:42 by hamezoua          #+#    #+#             */
/*   Updated: 2026/07/04 16:34:38 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	lock_dongles(t_coder *coder)
{
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
}

void	wait_for_dongles(t_coder *coder, int x)
{
	if (x == 1)
	{
		pthread_mutex_unlock(&coder->left_dongle->mutex);
		pthread_cond_wait(&coder->right_dongle->cond,
			&coder->right_dongle->mutex);
		pthread_mutex_unlock(&coder->right_dongle->mutex);
	}
	else
	{
		pthread_mutex_unlock(&coder->right_dongle->mutex);
		pthread_cond_wait(&coder->left_dongle->cond,
			&coder->left_dongle->mutex);
		pthread_mutex_unlock(&coder->left_dongle->mutex);
	}
}

void	take_dongles(t_coder *coder, t_config *config)
{
	long	priority;

	if (coder->config->scheduler == 1)
		priority = get_current_time();
	else
		priority = coder->config->time_to_burnout + coder->last_compile_start;
	lock_dongles(coder);
	heap_insert(coder->left_dongle, coder->id_of_coder, priority);
	heap_insert(coder->right_dongle, coder->id_of_coder, priority);
	while ((coder->left_dongle->heap[0].coder_id != coder->id_of_coder
			|| coder->right_dongle->heap[0].coder_id != coder->id_of_coder)
		&& is_dead(config) != 1)
	{
		if (coder->left_dongle->heap[0].coder_id != coder->id_of_coder)
			wait_for_dongles(coder, 0);
		else if (coder->right_dongle->heap[0].coder_id != coder->id_of_coder)
			wait_for_dongles(coder, 1);
		lock_dongles(coder);
	}
	if (get_current_time() - coder->left_dongle->last_released_time < coder->config->dongle_cooldown
		|| get_current_time() - coder->left_dongle->last_released_time < coder->config->dongle_cooldown)
		ft_usleep(coder->config->dongle_cooldown, coder);
}

void	drop_dongles(t_coder *coder)
{
	coder->left_dongle->last_released_time = get_current_time();
	coder->right_dongle->last_released_time = get_current_time();
	heap_extract_min(coder->left_dongle);
	heap_extract_min(coder->right_dongle);
	pthread_cond_broadcast(&coder->left_dongle->cond);
	pthread_cond_broadcast(&coder->right_dongle->cond);
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
}
