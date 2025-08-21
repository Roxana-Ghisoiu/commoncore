/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:28:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 11:31:31 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
isalnum()- checks  for  an  alphanumeric character;
it is equivalent to (isal‐pha(c) || isdigit(c)).
RETURN VALUE
The values  returned are nonzero if
the character c falls into the tested class,
and zero if not.*/

#include "libft.h"

int	ft_isalnum(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i >= '0'
			&& i <= '9'))
		return (1);
	return (0);
}
