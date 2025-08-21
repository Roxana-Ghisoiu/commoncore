/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:35:04 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 11:36:11 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
isascii()-checks whether c is a 7-bit unsigned char value
that fits into the ASCII character set.
RETURN VALUE
The  values  returned are nonzero if the character c falls
into the tested class, and zero if not.*/

#include "libft.h"

int	ft_isascii(int i)
{
	if (i >= 0 && i <= 127)
		return (1);
	return (0);
}
