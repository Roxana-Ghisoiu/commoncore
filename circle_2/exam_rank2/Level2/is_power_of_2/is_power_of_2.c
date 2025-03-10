/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:55:22 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/06 14:04:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	    is_power_of_2(unsigned int n)
{
	if (n == 0)
		return(0);
	return ((n &(n - 1)) == 0);
}

int main()
{
    unsigned int test_values[] = {0, 1, 2, 3, 4, 8, 10, 16, 32, 100};
    for (int i = 0; i < 10; i++)
    {
        printf("%d -> %s\n", test_values[i], is_power_of_2(test_values[i]) ? "DA" : "NU");
    }
    return 0;
}
