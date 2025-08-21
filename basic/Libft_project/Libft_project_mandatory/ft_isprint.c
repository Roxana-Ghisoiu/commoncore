/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:38:14 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 11:38:37 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
isprint()- checks for any printable character including space.
RETURN VALUE
The values returned are nonzero if the character c falls
into the tested class, and zero if not.*/

#include "libft.h"

int	ft_isprint(int i)
{
	if (i >= 32 && i <= 126)
		return (1);
	return (0);
}
