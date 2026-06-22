/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/16 17:59:20 by username         #+#    #+#              */
/*   Updated: 2026/06/22 14:19:35 by username        ###   ########.fr        */
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

void	ft_usleep(long time_in_ms)
{
	long	target_time;

	target_time = get_current_time() + time_in_ms;
	while (target_time > get_current_time())
	{
		usleep(1000);
	}
}
