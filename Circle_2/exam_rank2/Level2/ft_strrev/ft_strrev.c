/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:23:11 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/19 13:38:29 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char    *ft_strrev(char *str)
{
	int	i = 0;
	int	len = 0;
	char	temp;

	while(str[len])
		len++;
	while(i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - 1 -i];
		str[len -1 - i]= temp;
		i++;
	}
	return (str);
}

/*
#include <stdio.h>

int main(void)
{
    char str1[] = "Hello, 42!";
    char str2[] = "Palindrome";
    char str3[] = "A";
    char str4[] = "";

    // Copiem șirul original într-o variabilă temporară
    char temp1[] = "Hello, 42!";
    char temp2[] = "Palindrome";
    char temp3[] = "A";
    char temp4[] = "";

    printf("Original: \"%s\" | Reversed: \"%s\"\n", temp1, ft_strrev(str1));
    printf("Original: \"%s\" | Reversed: \"%s\"\n", temp2, ft_strrev(str2));
    printf("Original: \"%s\" | Reversed: \"%s\"\n", temp3, ft_strrev(str3));
    printf("Original: \"%s\" | Reversed: \"%s\"\n", temp4, ft_strrev(str4));

    return (0);
}
*/
