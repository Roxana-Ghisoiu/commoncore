/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:14:28 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 11:25:56 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
The bzero(void) function erases the data in the n bytes
of the memory starting at the location pointed to by s,
by writing zeros (bytes containing '\0') to that area.
The explicit_bzero(void) function performs the same task as bzero().
It differs from bzero() in that it guarantees that compiler
optimizations will not remove the erase operation if the compiler
deduces that the operation is "unnecessary".

RETURN VALUE
None.*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
