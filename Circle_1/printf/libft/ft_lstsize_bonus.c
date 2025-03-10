/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:27:37 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/25 17:38:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Initialize the Count:
start with	count = 0, as we haven’t counted any nodes yet.
Iterate Through the List:
As long as lst is not NULL,
we increment count and move to the next node
in the list with lst = lst->next.
Return the Count:
When lst becomes NULL, we have reached the end of the list,
and count contains the number of nodes.
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
