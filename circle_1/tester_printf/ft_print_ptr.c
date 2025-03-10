/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:28:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/02 19:51:08 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <stdint.h> 

int	ft_print_ptr(void *ptr)
{
	unsigned long	address;
	int				count;

	count = 0;
	address = (unsigned long)ptr;
	ft_putstr_fd("0x", 1);
	count += 2;
	if (address == 0)
	{
		ft_putchar_fd('0', 1);
		count += 1;
		return (count);
	}
	else
	{
		count += ft_print_num_base(address, 'x');
	}
	return (count);
}

int main()
{
    printf("Testing NULL pointer:\n");
    printf("Result: %d\n", ft_print_ptr(NULL));

    printf("\nTesting valid pointer:\n");
    int x = 42;
    printf("Result: %d\n", ft_print_ptr(&x));

    printf("\nTesting freed pointer:\n");
    int *y = malloc(sizeof(int));
    *y = 24;
    free(y);
    printf("Result: %d\n", ft_print_ptr(y));

    printf("\nTesting misaligned pointer:\n");
    char *misaligned = (char *)((uintptr_t)&x + 1);
    printf("Result: %d\n", ft_print_ptr(misaligned));

    return 0;
}
