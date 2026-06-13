/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/06/13 15:00:32 by username         #+#    #+#              */
/*   Updated: 2026/06/13 18:21:41 by username        ###   ########.fr        */
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
	{
		printf("please check your argument");
		return (0);
	}
}
