/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:36:04 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/26 11:52:02 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int     *ft_range(int start, int end)
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
		array[i] = start;
		
		if(start < end)
			start++;
		else
			start--;
		i++;
	}
	return (array);	
}
/*
#include <stdio.h>

int main(void)
{
    int *result;
    int i;

    // Test 1: Range (1, 3)
    result = ft_range(1, 3);
    printf("Range (1, 3): ");
    for (i = 0; i < 3; i++) // 3 este numărul de elemente
        printf("%d ", result[i]);
    printf("\n");
    free(result);

    // Test 2: Range (-1, 2)
    result = ft_range(-1, 2);
    printf("Range (-1, 2): ");
    for (i = 0; i < 4; i++) // 4 este numărul de elemente
        printf("%d ", result[i]);
    printf("\n");
    free(result);

    // Test 3: Range (0, 0)
    result = ft_range(0, 0);
    printf("Range (0, 0): ");
    printf("%d\n", result[0]); // Un singur element
    free(result);

    // Test 4: Range (0, -3)
    result = ft_range(0, -3);
    printf("Range (0, -3): ");
    for (i = 0; i < 4; i++) // 4 este numărul de elemente
        printf("%d ", result[i]);
    printf("\n");
    free(result);

    return (0);
}*/
