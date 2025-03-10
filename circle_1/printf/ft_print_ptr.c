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
#include "libft.h"

int	ft_print_ptr(void *ptr, int *i)
{
	unsigned long	address;

	address = (unsigned long)ptr;
	if (!ptr)
	{
		*i += write(1, "(nil)", 5);
		return (*i);
	}
	*i += write(1, "0x", 2);
	*i += ft_print_num_base(address, 'x');
	return (*i);
}
