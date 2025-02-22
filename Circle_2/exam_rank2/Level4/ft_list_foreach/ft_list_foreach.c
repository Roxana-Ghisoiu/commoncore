/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:42:48 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/10 18:44:40 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_list.h"

void    ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	while (begin_list)
	{
		if (f)
		(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}


void print_data(void *data)
{
	if (data) 
		printf("%d\n", *(int *)data);
}

int main()
{
	int a = 10, b = 20, c = 30;

	// Creare corectă a nodurilor
	t_list node3;
	node3.data = &c;
	node3.next = NULL;

	t_list node2;
	node2.data = &b;
	node2.next = &node3;

	t_list node1;
	node1.data = &a;
	node1.next = &node2;

	// Apelăm funcția
	ft_list_foreach(&node1, print_data);
	return 0;
}
