/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:00:59 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/05 11:01:28 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"

static int	handle_conversion(const char **format, va_list args)
{
	int	count;
	int	temp_count;

	count = 0;
	if (**format == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (**format == 's')
		count += ft_print_str(va_arg(args, char *));
	else if (**format == 'd' || **format == 'i')
		count += ft_print_num(va_arg(args, int));
	else if (**format == 'u')
		count += ft_print_num_unsigned(va_arg(args, unsigned int));
	else if (**format == 'x' || **format == 'X')
		count += ft_print_num_base(va_arg(args, unsigned int), **format);
	else if (**format == 'p')
	{
		temp_count = 0;
		ft_print_ptr(va_arg(args, void *), &temp_count);
		count += temp_count;
	}
	else if (**format == '%')
		count += write(1, "%", 1);
	else
		count += write(1, *format, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += handle_conversion(&format, args);
		}
		else
		{
			count += write(1, format, 1);
		}
		format++;
	}
	va_end(args);
	return (count);
}
