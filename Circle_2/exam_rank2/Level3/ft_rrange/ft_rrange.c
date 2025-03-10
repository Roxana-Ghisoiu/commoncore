/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:19:07 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/09 13:27:41 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int     *ft_rrange(int start, int end)
{
	int	*array;
	int	size;
	int	i;

	if (start <= end)
		size = end - start + 1;
	else
		size = start - end + 1;

	array = malloc(sizeof(int) * size);

	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		array[i] = end;
		if (end > start)
			end--;
		else
			end++;
		i++;
	}
	return (array);
}

#include <stdio.h>

int *ft_rrange(int start, int end);

int main()
{
	int *arr;
	int size;
	int i;

	arr = ft_rrange(1, 3);
	size = 3 - 1 + 1; // Dimensiunea corectă
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	free(arr);
	return 0;
}

