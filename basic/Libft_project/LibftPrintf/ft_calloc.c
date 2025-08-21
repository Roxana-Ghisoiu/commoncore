/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:27:54 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/23 12:40:12 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
The	calloc(void) function allocates memory for an array of nmemb
elements  of size bytes each and returns a pointer to the allocated memory.*/

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb != 0 && total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
