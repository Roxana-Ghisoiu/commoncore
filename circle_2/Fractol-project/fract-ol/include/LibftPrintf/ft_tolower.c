/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:01:12 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 17:01:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
These functions convert lowercase letters to uppercase, and vice versa.
RETURN VALUE
The value returned is that of the converted letter,
or c if the conversion was not possible.*/

#include "libft.h"

int	ft_tolower(int i)
{
	if (i >= 'A' && i <= 'Z')
		return (i + 32);
	return (i);
}
