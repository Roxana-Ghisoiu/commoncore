/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:44:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/05 12:53:49 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main (int ac, char **av)
{
	int	a;
	int	b;

	if (ac == 4)
	{
		a = atoi(av[1]);
		b = atoi(av[3]);

		if(av[2][0] == '+')
			printf("%d", a + b);
		else if (av[2][0] == '-')
			printf ("%d", a - b);
		else if (av[2][0] == '*')
			printf ("%d", a * b);
		else if (av[2][0] == '/')
			printf ("%d", a / b);
		else if (av[2][0] == '%')
			printf ("%d", a % b);
	}
	printf("\n");
	return (0);
}
