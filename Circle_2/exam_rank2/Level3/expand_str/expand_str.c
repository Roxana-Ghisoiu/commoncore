/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:45:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/22 12:04:20 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	c = 0;

	if(argc == 2)
	{
		i = 0;
		while(argv[1][i] == ' ' || argv[1][i] == '\t')
			i++;
		while(argv[1][i])
		{
			if(argv[1][i] == ' ' || argv [1][i] == '\t')
				c = 1;
			else
			{
				if(c)
					write(1, "   ", 3);
				c = 0;
				write(1, &argv[1][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return(0);
}

