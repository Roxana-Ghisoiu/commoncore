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

#include "libft.h"

int	ft_print_num_base(unsigned long num, char specifier)
{
	char	*base;
	int		length;
	int		count;

	count = 0;
	if (specifier == 'x')
		base = "0123456789abcdef";
	else if (specifier == 'X')
		base = "0123456789ABCDEF";
	else
		return (0);
	length = ft_strlen(base);
	if (num >= (unsigned long)length)
		count += ft_print_num_base(num / length, specifier);
	ft_putchar_fd(base[num % length], 1);
	count += 1;
	return (count);
}
