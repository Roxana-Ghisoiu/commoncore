/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:02:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/25 18:05:30 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The ft_lstdelone function is designed to delete
a single node in a linked list.
This function frees the content of the node using
a function provided as an argument (del) and then frees the node itself.*/

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
}
