/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:51:16 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 13:53:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The  memchr() function scans the initial n bytes of the memory
area pointed to by s for the first instance of c.
Both c and the bytes of the memory area pointed to by s
are interpreted as unsigned char.
RETURN VALUE
The  memchr() return a pointer to the matching byte or NULL
if the character does not occur in the given memory area.
  */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
