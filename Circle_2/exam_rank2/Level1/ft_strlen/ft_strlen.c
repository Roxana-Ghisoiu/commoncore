/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:15:05 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/14 17:41:10 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		i++;
	}
	return(i);
}

#include <stdio.h>

int	main(void)
{
	char str1[] = "Numele meu este";
	char str2[] = "Roxana";

	printf("lungimea a '%s': %d\n", str1, ft_strlen(str1));
	printf("lungimea a '%s': %d\n", str2, ft_strlen(str2));
}
