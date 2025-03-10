/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:14:57 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/02 19:40:13 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_print_num_base(unsigned int n, char specifier)
{
	char	*base;
	int		length;
	int		count;

	count = 0;
	if (specifier == 'X')
	{
		base = "0123456789ABCDEF";
	}
	else if (specifier == 'x')
	{
		base = "0123456789abcdef";
	}
	length = ft_strlen(base);
	if (n >= (unsigned int)length)
	{
		count += ft_print_num_base(n / length, specifier);
	}
	ft_putchar_fd(base[n % length], 1);
	count += 1;
	return (count);
}
