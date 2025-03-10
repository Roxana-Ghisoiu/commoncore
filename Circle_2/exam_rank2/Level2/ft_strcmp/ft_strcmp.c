/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:54:14 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/13 13:15:11 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>

int	ft_strcmp (char *s1, char *s2);

int	main (void)
{
	printf("Result 1:%d\n", ft_strcmp("Hello", "Hello"));
	printf("Result 2:%d\n", ft_strcmp("Hello", "World"));
}
*/

int	ft_strcmp (char *s1, char *s2)
{
	int	i = 0;
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return(s1[i] - s2[i]);
}
