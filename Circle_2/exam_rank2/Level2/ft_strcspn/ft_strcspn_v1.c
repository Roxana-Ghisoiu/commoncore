/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:10:01 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/18 18:24:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	count;
	size_t	i;

	count = 0;
	while(*s)
	{	
		i =0;
		while(reject[i] && *s != reject[i])
			i++;
		if (reject[i] != '\0')
			return count;
		count++;
		s++;
	}
	return (count);
}

#include <stdio.h>

int main(void)
{
    printf("%zu\n", ft_strcspn("abcdefg", "xyz"));  // Ar trebui să returneze 7
    printf("%zu\n", ft_strcspn("abcdefg", "ef"));   // Ar trebui să returneze 4
    printf("%zu\n", ft_strcspn("abcdefg", "g"));    // Ar trebui să returneze 6
    printf("%zu\n", ft_strcspn("abcdefg", ""));     // Ar trebui să returneze 7

    return 0;
}
