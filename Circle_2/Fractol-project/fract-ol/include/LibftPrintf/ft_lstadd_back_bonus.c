/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:51:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/25 18:00:17 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The ft_lstadd_back function adds a new node (new)
to the end of a linked list.
If the list is empty, new becomes the first and only node
Explanation:
If new is NULL, there’s no node to add, so the function simply returns.
Add new as the First Node if List is Empty:

If *lst is NULL, the list is empty,
so *lst (the head of the list) is set to new, making new the first node.
Find the Last Node and Append new:

If the list is not empty, ft_lstlast is called
to locate the last node in the list.
Once found, last->next is set to new, adding new to the end of the list.*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
