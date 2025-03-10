/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:05:16 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/10 17:19:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa (int nbr)
{
	long	n;
	int	len;
	char	*result;

	n = nbr;
	len = 0;
	
	if(n <= 0)
		len++;

	while(n != 0)
	{
		n /= 10;
		len++;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if(result == NULL)
		return(NULL);
		
	result[len] = '\0';
	
	n = nbr;
	
	if (n == 0)
	{
		result[0] ='0';
		return (result);
	}
	
	
	if (n < 0)
	{
		result[0] = '-';
		n= -n;
	}
	
	while(n > 0)
	{
		result[--len] = (n % 10) + '0';
		n /= 10;	
	}
	return (result);
}

#include <stdio.h>

int	main(void)
{
	printf("ft_itoa(123) = \"%s\"\n", ft_itoa(123));
	printf("ft_itoa(-42) = \"%s\"\n", ft_itoa(-42));
	printf("ft_itoa(0) = \"%s\"\n", ft_itoa(0));
	printf("ft_itoa(2147483647) = \"%s\"\n", ft_itoa(2147483647));
	printf("ft_itoa(-2147483648) = \"%s\"\n", ft_itoa(-2147483648));
	return (0);
}
