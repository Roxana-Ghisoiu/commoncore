/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:36:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/17 17:00:41 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int result = 0;
	int sign = 1;

	while(*str == ' ' || (*str >= '\t' &&  *str <= '\r'))
		str++;
	if(*str == '-' || *str == '+')
	{
		if(*str == '-')
			sign = -1;
		str++;
	}
	while(*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

#include <stdio.h>


int main(void)
{
	printf("%d\n", ft_atoi("   -12345"));   
	printf("%d\n", ft_atoi("+6789"));      
	printf("%d\n", ft_atoi("42abc123"));   
	printf("%d\n", ft_atoi("   +0"));     
	printf("%d\n", ft_atoi("2147483647")); 
	printf("%d\n", ft_atoi("-2147483648"));
	return 0;
}
