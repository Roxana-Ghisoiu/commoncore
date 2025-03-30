/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:40:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/25 17:47:46 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Explanation:
If lst is NULL, it means the list is empty, so we return NULL.
Iterate to the Last Node:
Using a while loop, we continue moving to the next node
until lst->next is NULL. When this condition is met,
lst points to the last node.
Return the Last Node:
Once we reach the end of the list,
lst (now pointing to the last node) is returned.*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
