/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:36:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 16:36:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
strlcat concatenates two strings (src and dst),
but ensures that the total length of the resulting string
does not exceed the specified size (size).
Returns
the length the attempted string would have had it not been limited by size.*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while (src[i] && (dst_len + i) < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
