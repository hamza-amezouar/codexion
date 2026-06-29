/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 14:07:50 by username          #+#    #+#             */
/*   Updated: 2026/06/29 10:00:49 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_insert(t_dongle *dongle, int coder_id, long priority)
{
	int			current;
	int			parrent;
	t_heap_node	temp;

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
			break ;
	}
}

int	heap_extract_min_helper(t_dongle *dongle, int current)
{
	int			smallest;
	int left_child;
	int right_child;
	t_heap_node	temp;

	smallest = current;
	left_child = (2 * current) + 1;
	right_child = (2 * current) + 2;
	if (left_child < dongle->heap_size &&\
		dongle->heap[left_child].priority \
		< dongle->heap[smallest].priority)
		smallest = left_child;
	if (right_child < dongle->heap_size && \
			dongle->heap[right_child].priority \
	< dongle->heap[smallest].priority)
		smallest = right_child;
	if (smallest != current)
	{
		temp = dongle->heap[smallest];
		dongle->heap[smallest] = dongle->heap[current];
		dongle->heap[current] = temp;
	}
	return (smallest);
}

void	heap_extract_min(t_dongle *dongle)
{
	int	current;
	int next_pos;

	current = 0;
	dongle->heap[0] = dongle->heap[dongle->heap_size - 1];
	dongle->heap_size--;
	while (1)
	{
		next_pos = heap_extract_min_helper(dongle, current);
		if (next_pos == current)
			break ;
		current = next_pos;
	}
}
