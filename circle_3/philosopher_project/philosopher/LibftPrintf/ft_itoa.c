/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:01:37 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 18:30:15 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * get_size - Determines the number of digits in a number (including sign).
 * @n: The number to analyze.
 * Return: The number of characters needed to store the number.
 */
static size_t	get_size(long n)
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
/**
 * ft_itoa - Converts an integer to a string.
 * @n: The integer to convert.
 * Return: A string representing the integer (must be freed).
 */

char	*ft_itoa( int n)
{
	char	*result;
	size_t	size;
	long	num;

	num = n;
	size = get_size(num);
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	result[size] = '\0';
	if (num == 0)
		result[0] = '0';
	else
	{
		if (num < 0)
			num = -num;
		while (num > 0)
		{
			result[--size] = (num % 10) + '0';
			num /= 10;
		}
		if (n < 0)
			result[0] = '-';
	}
	return (result);
}
