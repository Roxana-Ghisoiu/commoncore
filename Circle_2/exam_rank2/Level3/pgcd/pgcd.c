/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:45:14 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/09 16:52:35 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main (int argc, char **argv)
{
	int	num1;
	int	num2;
	int	swap;

	if (argc == 3)
	{
		if ((num1 = atoi(argv[1])) > 0 && (num2 = atoi(argv[2])) > 0)
		{
			while(num2 != 0)
			{
				swap = num2;
				num2 = num1 % num2;
				num1 = swap;
			}
			printf("%d",num1);
		}
	}
	printf("\n");
}

