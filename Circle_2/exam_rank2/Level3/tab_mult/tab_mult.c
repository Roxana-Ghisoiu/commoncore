/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:17:28 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/09 18:37:39 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	atoi (char *str)
{
	int	result = 0;

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	ft_putnbr (int n)
{
	char c;

	if (n >= 10)
		ft_putnbr(n/10);
	c = (n % 10) + '0';
	write (1, &c, 1);
}

int	main (int ac, char **av)
{
	int	i = 1;
	int	nbr = 0;

	if (ac == 2)
	{
		nbr = atoi(av[1]);

		while (i <= 9)
		{
			ft_putnbr(i);
			write (1," x ",3);
			ft_putnbr(nbr);
			write (1," = ", 3);
			ft_putnbr(i * nbr);
			write(1, "\n",1);
			i++;
		}
	}
	else
	write(1,"\n",1);
	return (0);
}
