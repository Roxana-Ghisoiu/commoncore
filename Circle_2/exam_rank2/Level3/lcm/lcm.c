/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:48:50 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/23 18:02:19 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int    lcm(unsigned int a, unsigned int b)
{
	unsigned int	n;
	
	if(a == 0 || b == 0)
		return(0);
	if(a >= b)
		n = a;
	else
		n = b;
	while (1)
	{
		if(n % a == 0 && n % b == 0)
			return(n);
		n++;
	}
}

#include <stdio.h>

unsigned int    lcm(unsigned int a, unsigned int b);

int main(void)
{
    printf("lcm(12, 18) = %u\n", lcm(12, 18)); // 36
    printf("lcm(7, 5) = %u\n", lcm(7, 5));     // 35
    printf("lcm(0, 10) = %u\n", lcm(0, 10));   // 0
    printf("lcm(21, 6) = %u\n", lcm(21, 6));   // 42
    printf("lcm(100, 25) = %u\n", lcm(100, 25)); // 100
    printf("lcm(8, 32) = %u\n", lcm(8, 32));   // 32
    return 0;
}
