/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:36:55 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/09 14:52:43 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>

typedef struct    s_list
{
	struct s_list *next;
	void          *data;
}                 t_list;

int	ft_list_size(t_list *begin_list)
{
	int	count = 0;

	while(begin_list)
	{
		count++;
		begin_list = begin_list -> next;
	}
	return (count);
}

int main()
{
    t_list a, b, c;

    a.next = &b;
    b.next = &c;
    c.next = NULL;

    printf("Număr de elemente: %d (așteptat: 3)\n", ft_list_size(&a));

    return 0;
}
