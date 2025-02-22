/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:39:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/02 16:02:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Function Purpose:
The ft_itoa function converts an integer n to its string
representation (essentially converting an int to a char *). For example,
given			n = 123, it will return "123". */

#include "libft.h"

static size_t	get_size(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	num;
	size_t	size;

	num = (long)n;
	size = get_size(n);
	if (n < 0)
	{
		num = -num;
	}
	result = (char *)malloc(size + 1);
	if (!result)
		return (NULL);
	result[size] = '\0';
	while (size > 0)
	{
		size--;
		result[size] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
