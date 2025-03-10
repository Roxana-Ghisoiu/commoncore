/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:48:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/20 13:56:11 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	char c;
	int	i = 7;

	while(i >= 0)
	{
		c = ((octet >> i) & 1) + '0';
		write(1, &c, 1);
		i--;
	}
}

int	main(void)
{
	print_bits(5);  // Ar trebui să afișeze: 00000101
	write(1, "\n", 1);
	print_bits(255); // Ar trebui să afișeze: 11111111
	write(1, "\n", 1);
	print_bits(0);  // Ar trebui să afișeze: 00000000
	write(1, "\n", 1);
	print_bits(170); // Ar trebui să afișeze: 10101010
	write(1, "\n", 1);
	return (0);
}
