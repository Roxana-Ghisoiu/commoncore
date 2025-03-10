/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:08:56 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/03 13:59:10 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

static void ft_putstr (const char *s, int *c)
{
	if(!s)
		s = "(null)";
	while (*s)
	{
		write (1, s++,1);
		(*c)++;
		
	}
}

static void ft_putnbr (int n, int *a)
{
	char	c;
	long	l = n;

	if (l < 0)
	{
		write (1, "-", 1);
		(*a)++;
		l = -l;
	}
	 if (l > 9)
		 ft_putnbr (l/10, a);
	 c = (l % 10) + '0';
	 write (1, &c,1);
	 (*a)++;
}

static void ft_puthex (unsigned int n, int *a)
{
	char *hex = "0123456789abcdef";
	char	c;

	if (n > 15)
		ft_puthex (n/16, a);
	c = hex [n % 16];
	write (1, &c,1);
	(*a)++;
}

int	ft_printf (const char *format, ...)
{
	va_list args;
	int	count = 0;

	va_start (args, format);

	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(args, char *), &count);
			else if (*format == 'd')
				ft_putnbr(va_arg(args, int), &count);
			else if (*format == 'x')
				ft_puthex (va_arg(args, unsigned int), &count);
			else
			{
				write (1, format, 1);
				count++;
			}
		}
		else
		{
			write (1, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

/*
int	main (void)
{
	int	rez1, rez2;

	rez1 = ft_printf ("%s\n","toto");
	rez2 = printf ("%s\n", "toto");
	printf("Return ft_printf: %d, Return printf: %d\n", rez1, rez2);

	rez1 = ft_printf ("Magic %s is %d\n", "number", 42);
	rez2 = printf ("Magic %s is %d\n", "number", 42);
	printf("Return ft_printf: %d, Return printf: %d\n", rez1, rez2);

	rez1 = ft_printf ("Hexadecimal for %d is %x\n", 42, 42);
        rez2 = printf ("Hexadecimal for %d is %x\n", 42, 42);
        printf("Return ft_printf: %d, Return printf: %d\n", rez1, rez2);

	return (0);

}
*/
