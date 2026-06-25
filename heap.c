/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 14:07:50 by hamezoua          #+#    #+#             */
/*   Updated: 2026/06/25 17:28:24 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void heap_insert(t_dongle *dongle, int coder_id, long priority)
{
    int     current;
    int     parrent;
    t_heap_node temp;
    dongle->heap[dongle->heap_size].coder_id = coder_id;
    dongle->heap[dongle->heap_size].priority = priority;
    dongle->heap_size++;
    current = dongle->heap_size - 1;
    while (current > 0)
    {
        parrent = (current - 1) / 2;
        if (dongle->heap[current].priority < dongle->heap[parrent].priority)
        {
            temp = dongle->heap[current];
            dongle->heap[current] = dongle->heap[parrent];
            dongle->heap[parrent] = temp;
            current = parrent;
        }
        else
            break;
    }
    
}

void    heap_extract_min(t_dongle *dongle)
{
    int     current;
    int right_child;
    int left_child;
    int smallest;
    t_heap_node temp;

    current = 0;
    dongle->heap[0] = dongle->heap[dongle->heap_size - 1];
    dongle->heap_size--;
    while(1)
    {
        smallest = current;
        left_child = (2 * current) + 1;
        right_child = (2 * current) + 2;
        if (left_child < dongle->heap_size && dongle->heap[left_child].priority < dongle->heap[smallest].priority)
        {
            smallest = left_child;
        }
        if (right_child < dongle->heap_size && dongle->heap[right_child].priority < dongle->heap[smallest].priority)
        {
            smallest = right_child;
        }
        if (smallest != current)
        {
            temp = dongle->heap[smallest];
            dongle->heap[smallest] = dongle->heap[current];
            dongle->heap[current] = temp;
            current = smallest;
        }
        else
            break;
    }
    
}