/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:42:06 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/19 11:52:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char    *ft_strdup(char *src)
{
	int	i = 0;
	char	*dest;

	while (src [i] != '\0')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if(!dest)
		return (NULL);
	i = 0;
	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char *copy = ft_strdup("Hello, 42!");
	
	if (copy == NULL)
		return (1);
	
	printf("%s\n", copy);
	free(copy);
	return (0);
}*/
