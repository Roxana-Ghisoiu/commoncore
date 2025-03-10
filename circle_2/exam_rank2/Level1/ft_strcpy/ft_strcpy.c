/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:04:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/14 16:39:27 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while(s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return(s1);
}
/*
#include <stdio.h>
int	main(void)
{
	char src[] = "Hello Roxi";
	char dest[50];

	ft_strcpy(dest, src);
	printf("Src: %s\n", src);
	printf("Dest: %s\n", dest);
}*/
