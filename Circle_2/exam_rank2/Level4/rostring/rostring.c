/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:39:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/13 17:04:24 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main (int argc, char **argv)
{
	char *str = argv[1], *start, *end;

	if(argc > 1)
	{
		while(*str == ' ' || *str == '\t')
			str++;
		start = str;
		while (*str && *str != ' ' && *str != '\t')
				str++;
		end = str;
		while (*str == ' ' || *str == '\t')
			str++;
		if(*str)
		{
			while(*str)
			{
				if(*str != ' ' && *str != '\t')
					write(1, str++, 1);
				else if(*(str+1) && (*(str+1) != ' ' && *(str + 1) != '\t'))
						write(1, " ", 1), str++;
				else
				    str++;
		}
		write(1, " ", 1);
	}
	write(1, start, end - start);
}
	write (1, "\n", 1);
	return(0);
}
