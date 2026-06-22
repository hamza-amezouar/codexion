/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.h                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/13 15:35:05 by username         #+#    #+#              */
/*   Updated: 2026/06/22 13:42:42 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_config;

typedef struct s_dongle
{
	int				id_of_dongle;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	long			last_released_time;

}	t_dongle;

typedef struct s_coder
{
	int			id_of_coder;
	long		last_compile_start;
	int			compile_count;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
}	t_coder;

typedef struct s_simulation
{
	t_config		*config;
	t_coder			*coders;
	t_dongle		*dongles;
	long			start_time;
	int				simulation_end;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;

}	t_simulation;

int				check_args(int argc, char **argv);
int				ft_atoi(char *str);
t_config		*ft_init(char **argv);
long			get_current_time(void);
void			ft_usleep(long time_in_ms);
t_simulation	*init_simulation(t_config *config);

#endif
