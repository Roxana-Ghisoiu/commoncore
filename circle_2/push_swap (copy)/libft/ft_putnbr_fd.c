/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:19:43 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 14:22:04 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*The function ft_putnbr_fd writes an integer to a specified file descriptor,
 supporting both positive and negative values.
It uses recursion to print the digits from the most
significant to the least significant, ensuring the correct order.
The function does not return a value (void),
as its purpose is to produce output directly.*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = (unsigned int)(n * -1);
	}
	else
		num = (unsigned int)n;
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	ft_putchar_fd(num % 10 + 48, fd);
}
