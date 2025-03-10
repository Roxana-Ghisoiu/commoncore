/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:11:11 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 12:11:27 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Checks if a string represents a valid integer number.
*/
int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*
** Checks if a number is within the valid integer range.
*/
int	is_valid_int(char *str)
{
	int	num;

	num = ft_atoi(str);
	if (num < INT_MIN || num > INT_MAX)
		return (0);
	return (1);
}

/*
** Checks if there are duplicate values in the array.
*/
int	has_duplicates(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
** Parses the arguments, validates them, and returns an array of integers.
*/
int	*parse_args(int argc, char **argv, int *size)
{
	int	*arr;
	int	i;

	*size = argc - 1;
	if (*size == 0)
		return (NULL);
	arr = malloc(sizeof(int) * (*size));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!is_number(argv[i + 1]) || !is_valid_int(argv[i + 1]))
		{
			free(arr);
			return (NULL);
		}
		arr[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	if (has_duplicates(arr, *size))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
