/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_capitalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:27:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/14 17:28:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;
	int	j;

	if (ac > 1)
	{
		j = 1;
		while (j < ac)
		{
			i = 0;
			while (av[j][i])
			{
				if (av[j][i] >= 'A' && av[j][i] <= 'Z')
					av[j][i] += 32;
				if ((av[j][i] >= 'a' && av[j][i] <= 'z')
					&& (av[j][i + 1] == ' ' || av[j][i + 1] == '\t' || av[j][i + 1] == '\0'))
					av[j][i] -= 32;
				write(1, &av[j][i], 1);
				i++;
			}
			write(1, "\n", 1);
			j++;
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}
