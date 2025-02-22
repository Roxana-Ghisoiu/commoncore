/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:59:01 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/26 17:09:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Explinations:
1. Verificare aparametrilor:
Dacă lst sau f este NULL, funcția se oprește imediat cu return,
prevenind accesarea unei valori nevalide.
2.Parcurgerea listei: În bucla while,
funcția f este aplicată la fiecare nod din listă prin f(lst->content).
3.Avansarea în listă: Cu lst = lst->next,
funcția avansează la următorul nod până când
lista s-a terminat (lst devine NULL).*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
