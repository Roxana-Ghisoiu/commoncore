/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:23:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/31 20:02:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The function ft_putstr_fd is designed to output a string
to a specified file descriptor, character by character.*/

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	if (!s || (fd < 0))
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

/*int	main(void)
{
	ft_putstr_fd("Hello, world!\n", 1);
	ft_putstr_fd(NULL, 1);
	return (0);*/
