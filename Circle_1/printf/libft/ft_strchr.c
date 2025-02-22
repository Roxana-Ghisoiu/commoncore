/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:19:29 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 16:20:49 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
The	strchr(void) function returns a pointer to the first
occurrence of the character c in the string s.
RETURN
functions return a pointer to the matched character or NULL
if the character is not found.  The terminating null byte is
considered  part of the string, so that if c is specified as '\0',
these functions return a pointer to the terminator.*/

#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	while (*s)
	{
		if (*s == (unsigned char)i)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)i == '\0')
		return ((char *)s);
	return (NULL);
}
