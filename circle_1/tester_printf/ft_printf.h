/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:40:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/31 19:13:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *format, ...);

int	ft_print_char(char c);
int	ft_print_str(char *str);
int	ft_print_num(int n);
int	ft_print_num_unsigned(unsigned int n);
int	ft_print_num_base(unsigned int n, char specifier);
int	ft_print_ptr(void *ptr);

#endif
