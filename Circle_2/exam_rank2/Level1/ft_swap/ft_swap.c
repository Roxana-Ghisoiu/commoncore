/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:51:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/14 17:59:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

#include <stdio.h>

int main(void)
{
    int x = 42;
    int y = 24;

    printf("Before swapping: x = %d, y = %d\n", x, y);

    ft_swap(&x, &y);

    printf("After swapping: x = %d, y = %d\n", x, y);

    return 0;
}
