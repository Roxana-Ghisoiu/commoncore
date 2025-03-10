/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:40:16 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/21 12:05:03 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

int	ft_is_prime(int num)
{
	int	i;

	if(num <= 1)
		return(0);
	i = 2;
	while( i * i <= num)
	{
		if(num % i == 0)
			return(0);
		i++;
	}
	return(1);
}

int	ft_atoi(const char *str)
{
	int	result = 0;

	while(*str >= '0' && *str <= '9')
	{
		result = result * 10 +(*str - '0');
		str++;
	}
	return (result);
}

void	ft_putnbr( int n)
{
	char	c;

	if(n >= 10)
		ft_putnbr(n/10);
	c = (n % 10) + '0';
	write(1, &c, 1);

}

int	main(int argc, char **argv)
{
	int num;
	int sum;

	if(argc == 2)
	{
		num = ft_atoi(argv[1]);
		sum = 0;
		while(num > 0)
		{
			if(ft_is_prime(num))
				sum += num;
			num--;
		}
		ft_putnbr(sum);
	}
	else
	ft_putnbr(0);
	write(1, "\n", 1);
	return(0);
}
