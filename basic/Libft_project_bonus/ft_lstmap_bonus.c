/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:12:09 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/26 17:26:55 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Funcția ft_lstmap primește o listă de noduri lst,
o funcție f pe care trebuie să o aplice pe conținutul
fiecărui nod din lst și o funcție del folosită pentru
a șterge conținutul nodurilor în cazul unei erori.
Scopul este de a crea o nouă listă de noduri,
fiecare conținând rezultatul aplicării funcției f asupra nodurilor din lst.
new_list: Este lista nouă, care va conține nodurile
rezultate după aplicarea funcției f.
new_node: Este un nod temporar, folosit
pentru a crea și adăuga noduri noi la new_list.
Funcția intră într-un while care parcurge
nodurile din lst până la final n acest fel, 
ft_lstmap îți oferă o listă nouă, bazată pe lista originală, 
dar cu datele prelucrate, menținând și o gestionare corectă a memoriei.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
