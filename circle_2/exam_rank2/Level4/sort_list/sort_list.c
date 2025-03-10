/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:40:17 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/10 17:51:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
/*
typedef struct s_list
{
	int data;
	struct s_list *next;
} t_list;
*/

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
	int	swap;
	t_list	*start;
	
	if(!lst)
	return (NULL);
	
	start = lst;
	while(lst != NULL && lst ->next != NULL)
	{
		if ((*cmp)(lst->data, lst->next->data) > 0)
		{
			swap = lst -> data;
			lst -> data = lst -> next -> data;
			lst->next->data = swap;
			lst = start;
		}
		else
			lst  = lst -> next;
	}
	return(start);
}

/*

int	ascending(int a, int b)
{
	return (a - b);
}

t_list *create_node(int value)
{
	t_list *new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = value;
	new->next = NULL;
	return (new);
}

void print_list(t_list *head)
{
	while (head)
	{
		printf("%d -> ", head->data);
		head = head->next;
	}
	printf("NULL\n");
}

int main(void)
{
	t_list *head = create_node(4);
	head->next = create_node(2);
	head->next->next = create_node(5);
	head->next->next->next = create_node(1);
	head->next->next->next->next = create_node(3);

	printf("Lista inițială:\n");
	print_list(head);

	head = sort_list(head, ascending);

	printf("Lista sortată:\n");
	print_list(head);

	t_list *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return (0);
}*/
