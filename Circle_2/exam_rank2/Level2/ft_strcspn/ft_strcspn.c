/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftstrcspn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:31:51 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/29 14:46:13 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strcspn (const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while(s[i] != '\0')
	{
		j = 0;
		while(reject[j] != '\0')
		{
			if (reject[j] == s[i])
				return(i);
			j++;
		}
		i++;
	}
	return (i);
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
