/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:06:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 17:15:01 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_num(int n)
{
	char	*num;
	int		len;

	num = ft_itoa(n);
	if (!num)
		return (0);
	ft_putstr_fd(num, 1);
	len = ft_strlen(num);
	free(num);
	return (len);
}
