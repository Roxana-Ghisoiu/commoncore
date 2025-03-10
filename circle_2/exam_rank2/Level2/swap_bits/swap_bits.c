/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:19:39 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/06 15:26:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}

#include <stdio.h>

int main(void)
{
    unsigned char test1 = 0b11010010;  // 210 în zecimal
    unsigned char test2 = 0b10101010;  // 170 în zecimal
    unsigned char test3 = 0b11110000;  // 240 în zecimal
    unsigned char test4 = 0b00001111;  // 15 în zecimal

    printf("Test 1: %u -> Swapped: %u\n", test1, swap_bits(test1));  // Așteptăm 157
    printf("Test 2: %u -> Swapped: %u\n", test2, swap_bits(test2));  // Așteptăm 85
    printf("Test 3: %u -> Swapped: %u\n", test3, swap_bits(test3));  // Așteptăm 15
    printf("Test 4: %u -> Swapped: %u\n", test4, swap_bits(test4));  // Așteptăm 240

    return 0;
}

