/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:00:32 by hamezoua          #+#    #+#             */
/*   Updated: 2026/06/13 16:50:54 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// int main(int argc, char **argv)
// {
//     int valid;

//     valid = check_args(argc, argv);
// }

int main(int argc, char **argv)
{
    if (check_args(argc,argv) == -1)
    {
        printf("please check your argument");
        return 0;
    }
}