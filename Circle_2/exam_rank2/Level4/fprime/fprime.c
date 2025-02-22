/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:19:04 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/15 12:25:56 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main (int ac, char **av)
{
	int	nbr;
	int	i;

	if (ac == 2)
	{
		nbr = atoi(av[1]);
		i = 2;
		while (i <= nbr)
		{
			if (nbr % i == 0)
			{
				printf ("%d", i);
				nbr /= i;
				if (nbr > 1)
					printf ("*");
			}
			else
				i++;
		}
	}
	printf("\n");
	return (0);
}
