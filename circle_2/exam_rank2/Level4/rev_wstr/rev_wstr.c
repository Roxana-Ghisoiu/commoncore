/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:55:55 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/22 13:09:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i = 0;
	int	start = 0;
	int	end = 0;
	int	flag = 0;

	if(ac == 2)
	{
		while(av[1][i])
			i++;
		i--;
		while ( i >= 0)
		{
			while( i >= 0 &&(av[1][i] == ' ' || av[1][i] == '\t'))
				i--;
			end = i;

			while( i >= 0 && av[1][i] != ' ' && av[1][i] != '\t')
				i--;
			start = i + 1;

			if(end >= start)
			{
				if(flag)
					write(1, " ", 1);
				while(start <= end)
				{
					write(1,&av[1][start],1);
					start++;
				}
				flag = 1;
			}
		}
	}
	write(1,"\n", 1);
	return(0);
}
