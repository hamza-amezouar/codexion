/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamezoua <amouzwarh+1@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 16:26:49 by username          #+#    #+#             */
/*   Updated: 2026/06/27 14:55:20 by hamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
//  * Definition for singly-linked list.
struct ListNode {
	int val;
	struct ListNode *next;
};

int rotate_numbers(struct ListNode* Node)
{
	int total;
	int *arr;
	int total_nodes = 0;
	total = 0;
	
	while(Node != NULL)
	{
		total_nodes++;
		
	}
	arr = malloc(sizeof(int) * total_nodes);
	
	return total;
}
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int val_l1;
    int val_l2;

    val_l1 = 0;
    val_l2 = 0;
    struct ListNode* temp;
    temp = l1;
    while (temp != NULL)
    {
        val_l1 += temp->val;
        temp = temp->next;
    }
	temp = l2;
	while (temp != NULL)
    {
        val_l2 += temp->val;
        temp = temp->next;
    }
	
	printf("val1 = %d, val 2 = %d", val_l1, val_l2);
}

int main(void)
{
	struct ListNode *l1;
	struct ListNode *l11;
	struct ListNode *l2;
	struct ListNode *l22;

	l1 = malloc(sizeof(struct ListNode));
	l11 = malloc(sizeof(struct ListNode));
	l2 = malloc(sizeof(struct ListNode));
	l22 = malloc(sizeof(struct ListNode));
	l1->val = 10;
	l1->next = l11;
	l1->next->val = 20;
	l1->next->next = NULL;
// l1 ***********************************************8

	l2->val = 40;
	l2->next = l22;
	l2->next->val = 50;
	l2->next->next = NULL;
	
	int x = rotate_numbers(l1);
	
	printf("%d", x);
}
