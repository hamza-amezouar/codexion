/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:00:32 by username          #+#    #+#             */
/*   Updated: 2026/06/15 18:30:58 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// int main(int argc, char **argv)
// {
//     int valid;

//     valid = check_args(argc, argv);
// }

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) == -1)
		return (0);
	// t_config	*s_config;
	// s_config = ft_init(argv);
	// // printf("%d",s_config->scheduler);
}
