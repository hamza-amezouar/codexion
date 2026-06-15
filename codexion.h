/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:35:05 by username          #+#    #+#             */
/*   Updated: 2026/06/15 18:28:02 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
#include <stdlib.h>

typedef struct s_config{
    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int  time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    int scheduler;
    
}t_config;


int	check_args(int argc, char **argv);
int	ft_atoi(char *str);
t_config *ft_init(char **argv);

#endif
