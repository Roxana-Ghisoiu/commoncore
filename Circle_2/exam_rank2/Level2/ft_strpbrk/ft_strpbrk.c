/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:10:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/19 12:23:55 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;

	if(!s1 || !s2)
		return (0);
	while(*s1)
	{
		i = 0;
		while(s2[i])
		{
			if(*s1 == s2[i])
				return((char *) s1);
			i++;	
		}
		s1++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	const char *s1 = "abcdefg";
	const char *s2 = "xyc";
	char *result;

	result = ft_strpbrk(s1, s2);
	if (result)
		printf("First matching character: %c\n", *result);
	else
		printf("No matching character found.\n");

	return (0);
}*/
