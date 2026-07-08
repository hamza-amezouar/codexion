/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:20:55 by hamezoua          #+#    #+#             */
/*   Updated: 2026/07/08 18:07:55 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

/* ************************************************************************** */
/* Headers                                                                    */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

/* ************************************************************************** */
/* Structures                                                                 */
/* ************************************************************************** */

/* Node used in the mini-heap for priority scheduling */
typedef struct s_heap_node
{
	int			coder_id;
	long		priority;
}				t_heap_node;

/* Global configuration parameters for the simulation */
typedef struct s_config
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				simulation_dead;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	int				is_cond;
	int				scheduler;
	long			start_time;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	brodcast_mutex;
}					t_config;

/* Shared resource (Dongle) status and priority queue */
typedef struct s_dongle
{
	int				id_of_dongle;
	int				waiting_threads;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	long			last_released_time;
	t_heap_node		*heap;
	int				heap_size;
}					t_dongle;

/* Coder (Thread) state and its assigned dongles */
typedef struct s_coder
{
	int				id_of_coder;
	int				compile_count;
	long			last_compile_start;
	pthread_mutex_t	mutex_time;
	t_config		*config;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t		thread;
}					t_coder;

/* Main simulation structure containing all elements */
typedef struct s_simulation
{
	t_config		*config;
	t_coder			*coders;
	t_dongle		*dongles;
}					t_simulation;

/* ************************************************************************** */
/* Function Prototypes                                                        */
/* ************************************************************************** */

int				check_args(int argc, char **argv);
int				ft_atoi(char *str);
t_config		*ft_init(char **argv);
long			get_current_time(void);
t_simulation	*init_simulation(t_config *config);
void			ft_usleep(long time_in_ms, t_coder *coder);
void			heap_insert(t_dongle *dongle, int coder_id, long priority);
void			heap_extract_min(t_dongle *dongle);
int				is_dead(t_config *config);
void			*coder_routine(void *arg);
void			drop_dongles(t_coder *coder);
void			take_dongles(t_coder *coder);
void			*monitor_routine(void *arg);

#endif