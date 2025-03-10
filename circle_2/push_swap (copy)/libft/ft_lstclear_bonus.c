/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:08:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/25 18:19:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The ft_lstclear function is designed to delete and free an entire linked list,
starting from a given node.
It applies a delete function (del) to each node’s content,
freeing each node and setting the list pointer to NULL afterward.
This function ensures that all nodes are properly freed,
preventing memory leaks when the list is no longer needed.

1. If either lst or del is NULL, the function does nothing.
2.Iterate Through the List:
The function uses a while loop to go through each node in the list.
temp stores the address of the next node,
which allows us to delete the current node
without losing the link to the rest of the list.
3.Delete Each Node:
ft_lstdelone is called with the current node (*lst)
and del to delete the node's content and free the node itself.
*lst is then updated to temp, moving to the next node.
4.Set the List Pointer to NULL:
After the loop completes, *lst is set to NULL,
ensuring that the original pointer no longer references any freed memory.*/

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
