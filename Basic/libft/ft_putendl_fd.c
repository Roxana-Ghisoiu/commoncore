/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:11 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 14:18:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The ft_putendl_fd function combines the functionality
of writing a string and appending a newline in a clean and concise manner.*/
#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
