/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:23:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 17:12:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The function ft_putstr_fd is designed to output a string
to a specified file descriptor, character by character.*/

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
