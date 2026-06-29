/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:59:20 by username          #+#    #+#             */
/*   Updated: 2026/06/29 15:06:40 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_current_time(void)
{
	struct timeval	time;
	long			millisecond;

	gettimeofday(&time, NULL);
	millisecond = (time.tv_sec * 1000) + (time.tv_usec / 1000);;
	return (millisecond);
}

void	ft_usleep(long time_in_ms, t_coder *coder)
{
	long	target_time;

	target_time = get_current_time() + time_in_ms;
	while (target_time > get_current_time())
	{
		if (is_dead(coder->config) == 1)
			break;
		usleep(500);
	}
}
