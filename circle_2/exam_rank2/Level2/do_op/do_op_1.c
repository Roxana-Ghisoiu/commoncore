/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:29:57 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/18 17:51:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "do_op.h"

void	do_op(int ac, char **av)
{
	int	a;
	int	b;
	int	result;

	if( ac == 4)
	{
		a = atoi(av[1]);
		b = atoi(av[3]);
		result = 0;
		if(av[2][0] == '+')
			result = a + b;
		else if(av[2][0] == '-')
			result = a - b;
		else if(av[2][0] == '*')
			result = a * b;
		else if(av[2][0] == '/' && b != 0)
			result =  a / b;
		else if (av[2][0] =='%' && b != 0)
			result = a % b;
	       printf("%d\n", result);	       
	}
	write(1, "\n", 1);
}

int	main(int ac, char **av)
{
	do_op(ac, av);
	return(0);
}
