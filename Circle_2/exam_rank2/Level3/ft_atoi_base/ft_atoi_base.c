/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:03:24 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/14 20:03:40 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi_base(const char *str, int str_base)
{
	int	value;
	int	result;
	int	sign;

	if (str_base < 2 || str_base > 16)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			value = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			value = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			value = *str - 'A' + 10;
		else
			break;
		if (value >= str_base)
			return (0);

		result = result * str_base + value;
		str++;

	}
	return (result * sign);
}


int main() {
    // Testare funcție ft_atoi_base
    const char *str1 = "1a";
    int base1 = 16;
    int result1 = ft_atoi_base(str1, base1);
    printf("Rezultatul conversiei pentru \"%s\" în baza %d este: %d\n", str1, base1, result1); // Ar trebui să afișeze 26

    const char *str2 = "-101";
    int base2 = 2;
    int result2 = ft_atoi_base(str2, base2);
    printf("Rezultatul conversiei pentru \"%s\" în baza %d este: %d\n", str2, base2, result2); // Ar trebui să afișeze -5

    const char *str3 = "7F";
    int base3 = 16;
    int result3 = ft_atoi_base(str3, base3);
    printf("Rezultatul conversiei pentru \"%s\" în baza %d este: %d\n", str3, base3, result3); // Ar trebui să afișeze 127

    const char *str4 = "123";
    int base4 = 8;
    int result4 = ft_atoi_base(str4, base4);
    printf("Rezultatul conversiei pentru \"%s\" în baza %d este: %d\n", str4, base4, result4); // Ar trebui să afișeze 83

    return 0;
}

