/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:12:48 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 13:12:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/**
 * @brief Sorts an array of integers using Bubble Sort.
 */
void	sort_array(int *arr, int size)
{
	int	temp;
	int	swapped;
	int	i;

	if (!arr || size < 2)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < size - 1)
		{
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}

/**
 * @brief Assigns an index to each element in stack A based on sorted order.
 */
void	index_stack(t_stack *a, int *arr, int size)
{
	t_node	*current;
	int		i;

	current = a->top;
	while (current)
	{
		i = 0;
		while (i < size)
		{
			if (current->value == arr[i])
			{
				current->index = i + 1;
				break ;
			}
			i++;
		}
		current = current->next;
	}
}

void	prepare_stack_for_radix(t_stack *a)
{
	int		*arr;
	int		size;
	int		i;
	t_node	*current;

	size = stack_size(a);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return ;
	current = a->top;
	i = 0;
	while (current)
	{
		arr[i++] = current->value;
		current = current->next;
	}
	sort_array(arr, size);
	index_stack(a, arr, size);
	free(arr);
}

void	execute_radix_sort(t_stack *a, t_stack *b, int max_bits,
		int initial_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < max_bits)
	{
		j = initial_size;
		while (j--)
		{
			if (!a || !a->top)
				return ;
			if (((a->top->index >> i) & 1) == 0)
				pb(a, b);
			else
				ra(a);
		}
		while (stack_size(b) > 0)
			pa(a, b);
		i++;
	}
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	size;

	size = stack_size(a);
	if (size < 2)
		return ;
	prepare_stack_for_radix(a);
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	execute_radix_sort(a, b, max_bits, size);
}
