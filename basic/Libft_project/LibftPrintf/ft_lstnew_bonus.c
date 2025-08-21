/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:50:12 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/25 17:25:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*This structure represents each node in a singly linked list:
->content- holds a pointer to any data type (void pointer allows flexibility).
->next- is a pointer to the next node in the list,
and it’s initially set to NULL for a new node.
1. Malloc allocates memory for a t_list structure to hold the new node.
If malloc fails, it returns NULL, so we check for this case and
return NULL if the allocation fails.
2. Initialization:
new_node->content = content; initializes the content field of
the new node with the value passed as the content parameter.
new_node->next = NULL; sets the next pointer of the new node to NULL,
indicating it’s the last node in the list for now.
Return Value:
The function returns a pointer to the newly created node
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
