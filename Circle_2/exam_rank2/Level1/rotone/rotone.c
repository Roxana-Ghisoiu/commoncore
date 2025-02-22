/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:55:48 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/25 15:02:24 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i = 0;
	char	c;

	if(argc == 2)
	{
		while(argv[1][i])
		{
			c = argv[1][i];
			if(c >= 'a' && c <= 'z')
			{
				if(c == 'z')
					c = 'a';
				else
					c = c + 1;

			}
			else if(c >= 'A' && c <= 'Z')
			{
				if(c == 'Z')
					c = 'A';
				else
					c = c + 1;

			}
			write (1,&c, 1);
			i++;
		}
	}
	write(1,"\n", 1);
	return(0);
}
