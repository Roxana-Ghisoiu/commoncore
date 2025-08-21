/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:55:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 13:56:20 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
The	memcmp(void)- function compares the first n bytes
(each interpreted as unsigned char) of the memory areas s1 and s2*.

RETURN VALUE
The	memcmp(void) function returns an integer less than, equal to,
or greater than zero if the first n bytes of
s1 is found, respectively, to be less than, to match,
or be greater than the first n bytes of s2.*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
