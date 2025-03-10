/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:06:25 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/20 13:22:30 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>

int	max(int* tab, unsigned int len)
{
	unsigned int i = 1;
	int	result = 0;

	if(len == 0)
		return(0);
	result = tab[0];
	while(i < len)
	{
		if(result < tab[i])
			result = tab[i];
		i++;
	}
	return result;
}
int main()
{
    int tab[] = {0, 1, 22, 10};
    int result = max(tab, 4);
    printf("%d\n", result);
    return (0);
}
