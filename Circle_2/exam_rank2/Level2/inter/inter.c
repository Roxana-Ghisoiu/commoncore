/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:53:02 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/19 17:20:08 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	int i;
	int j;
	unsigned char seen[256] = {0};

	if(ac == 3)
	{
		i = 0;
		while(av[1][i])
		{
			j = 0;
			while(av[2][j])
			{
				if(av[1][i] == av[2][j])
				{
					if(!seen[(unsigned char) av[1][i]])
					{
						write(1,&av[1][i], 1);
						seen[(unsigned char)av[1][i]] = 1;
					}
					break;
				}
				j++;
			}
			i++;
		}
	}
	write(1,"\n", 1);
}
