/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:19:39 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/19 16:25:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	count;
	size_t	i;
	
	count = 0;
	while(*s)
	{
		i = 0;
		while(accept[i] && *s != accept[i])
			i++;
		if(accept[i] == '\0')
			return count;
		count++;
		s++;
	}
	return (count);
}

#include <stdio.h>

int main() {
    const char *s = "abcde12345";
    const char *accept = "abcde";
    size_t result = ft_strspn(s, accept);
    printf("Length of the initial segment: %zu\n", result);
    return 0;
}
