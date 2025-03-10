/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:49:27 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 16:55:58 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
The	strrchr(void) function returns a pointer to the last occurrence
of the character c in the string s.
 RETURN
strrchr() functions return a pointer to the matched character or
NULL if the character is not found.
The terminating null byte is  considered  part
of  the string, so that if c is specified as '\0',
these functions return a pointer to the terminator.*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
