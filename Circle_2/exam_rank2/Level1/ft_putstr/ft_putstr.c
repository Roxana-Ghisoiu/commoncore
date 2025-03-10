/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:34:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/14 13:44:32 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	int i = 0;
	while(str[i])
		write(1, &str[i++], 1);
}


/*
int	main(void)

{
	ft_putstr("Hello, Roxana\n");
	ft_putstr(" \n");
	ft_putstr("FizzBuzz\n42 School\n");
	return (0);
}
*/
