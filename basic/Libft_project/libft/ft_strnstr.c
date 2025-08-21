/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:48:57 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 16:49:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (needle == NULL || needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < n)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && (i + j) < n)
			{
				if (haystack[i + j] != needle[j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
