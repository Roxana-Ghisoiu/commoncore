/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:46:34 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 16:47:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
 The  strncmp() function  is similar, except
 it compares only the first(at most) n bytes of s1 and s2.
RETURN
strncmp() functions return an integer  less  than,  equal  to,  or greater
than  zero if s1 (or the first n bytes thereof) is found, respectively, to
be less than, to match, or be greater than s2.*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	z;

	z = 0;
	if (n == 0)
		return (0);
	while (z < n && (s1[z] != '\0' || s2[z] != '\0'))
	{
		if (s1[z] != s2[z])
			return ((unsigned char)s1[z] - (unsigned char)s2[z]);
		z++;
	}
	return (0);
}
