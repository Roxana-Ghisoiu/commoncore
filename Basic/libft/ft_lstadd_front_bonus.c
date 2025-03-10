/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:04:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/25 17:10:28 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Parameter Checks:

If new is NULL, we do nothing, as there’s no new node to add.
 * Point 'new->next' to the current head of the list
	*lst = new;       Update the head of the list to be 'new'*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
