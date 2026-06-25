/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:59:20 by username          #+#    #+#             */
/*   Updated: 2026/06/24 15:19:56 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_current_time(void)
{
	struct timeval	time;
	long			sec;
	long			usec;
	long			millisecond;

	gettimeofday(&time, NULL);
	sec = time.tv_sec * 1000;
	usec = time.tv_usec;
	printf("usc  %ld", usec);
	millisecond = sec + usec;
	return (millisecond);
}

void	ft_usleep(long time_in_ms, t_coder *coder)
{
	long	target_time;

	target_time = get_current_time() + time_in_ms;
	while (target_time > get_current_time())
	{
		if (coder->config->simulation_dead == 1)
			break;
		usleep(1000);
	}
}
