/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 16:26:49 by username          #+#    #+#             */
/*   Updated: 2026/06/25 20:50:37 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "codexion.h"
#include <stdio.h>


int *mini_heap(int *arr, int size)
{
	for (int i = 1; i < size; i++)
	{
    	int current = i;
		
    	while (current > 0)
    	{
    	    int parent = (current - 1) / 2;
		
    	    if (arr[current] < arr[parent])
    	    {
    	        int tmp = arr[current];
    	        arr[current] = arr[parent];
    	        arr[parent] = tmp;
			
    	        current = parent;
    	    }
    	    else
    	        break;
    	}
	}
	
}
int main(void)
{
	int		i;
	int *ptr;
	int arr[10] = {3432,23,78,1,43534,435};
	i = 0;
	while (arr[i])
	{
		printf("%d\n", arr[i]);
		i++;
	}
	printf("\n\n");
	i = 0;
	ptr = mini_heap(arr, 6);
	while (ptr[i])
	{
		printf("%d\n", ptr[i]);
		i++;
	}
}
