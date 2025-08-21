/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:37:04 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 11:37:31 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
isdigit()- checks for a digit (0 through 9).
RETURN VALUE
The  values  returned are nonzero if the character c falls
into the tested class, and zero if not.*/

#include "libft.h"

int	ft_isdigit(int i)
{
	if ('0' <= i && i <= '9')
		return (1);
	return (0);
}
