/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:24:36 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 16:26:31 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*The ft_striteri function is used to iterate over a string (s),
and for each character, it applies a function f passed as a parameter. */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
