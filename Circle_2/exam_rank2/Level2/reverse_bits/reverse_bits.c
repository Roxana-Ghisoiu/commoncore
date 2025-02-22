/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:21:31 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/20 14:39:04 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char c = 0;
	int	i = 7;

	while(i >= 0)
	{
		c = (c << 1) | (octet & 1);
		octet = (octet >> 1);
		i--;
	}
	return (c);
}

#include <stdio.h>

int main(void)
{
    unsigned char test1 = 5;   // 00000101 -> 10100000
    unsigned char test2 = 255; // 11111111 -> 11111111
    unsigned char test3 = 0;   // 00000000 -> 00000000
    unsigned char test4 = 170; // 10101010 -> 01010101

    printf("%u\n", reverse_bits(test1));  // Așteptăm 160 (10100000)
    printf("%u\n", reverse_bits(test2));  // Așteptăm 255 (11111111)
    printf("%u\n", reverse_bits(test3));  // Așteptăm 0 (00000000)
    printf("%u\n", reverse_bits(test4));  // Așteptăm 85 (01010101)

    return 0;
}
