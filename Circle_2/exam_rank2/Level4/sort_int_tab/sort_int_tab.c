/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:13:17 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/15 14:22:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void sort_int_tab(int *tab, unsigned int size)
{
	int swap;
	unsigned int i = 0;
	unsigned int sorted;

	if (size < 2)
		return;
		
	sorted = 0;
	while(!sorted)
	{
		sorted = 1;
		i = 0;
		while(i < size - 1)
		{
			if(tab[i] > tab[i + 1])
			{
				swap = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = swap;
				sorted = 0;
			}
			else
				i++;
		}
	}
}

#include <stdio.h>

void print_array(int *tab, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
        printf("%d ", tab[i]);
    printf("\n");
}

int main()
{
    int arr[] = {5, 2, 9, 1, 5, 6};
    unsigned int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array inițial: ");
    print_array(arr, size);

    sort_int_tab(arr, size);

    printf("Array sortat: ");
    print_array(arr, size);

    return 0;
}
