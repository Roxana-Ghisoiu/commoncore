/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:06:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/02 12:28:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "printf.h"

int	ft_print_num(int n)
{
	char	*num_str;
	int		len;

	num_str = ft_itoa(n);
	if (!num_str)
		return (-1);
	ft_putstr_fd(num_str, 1);
	len = ft_strlen(num_str);
	free(num_str);
	return (len);
}
