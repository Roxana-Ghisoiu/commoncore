/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:21:16 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 18:08:15 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_print_str - Prints a string safely.
 * @str: The string to print.
 * Return: The number of characters printed.
 */
int	ft_print_str(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1), 6);
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}
