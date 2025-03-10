/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:08:39 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 14:09:44 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*DESCRIPTION
The memset(void) function fills the first n bytes
of the memory area pointed to by s with the constant byte c.
RETURN VALUE
The memset(void) function returns a pointer to the memory area s.*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
