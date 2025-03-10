/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:44:13 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/31 19:57:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
The	strlen(void) function  calculates the length
of the string pointed to by s,
excluding the terminating null byte ('\0').

RETURN VALUE
The	strlen(void) function returns the number
of bytes in the string pointed to by s.*/

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/*int main()
{
    printf("Length of 'Hello': %zu\n", ft_strlen("Hello"));
    printf("Length of '': %zu\n", ft_strlen(""));
    printf("Length of NULL: %zu\n", ft_strlen(NULL)); // Should return 0
    return 0;
}*/
