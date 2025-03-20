/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:23:49 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/25 11:24:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Implements the sorting algorithm for push_swap.
 *
 * This function sorts stack `a` using stack `b` as auxiliary storage.
 * It applies the most efficient sorting algorithm based on the stack size.
 *
 * @param a The main stack to be sorted.
 * @param b The auxiliary stack used during sorting.
 */
void	push_swap(t_stack *a, t_stack *b)
{
	int	size;

	size = stack_size(a);
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else if (size <= 5)
		sort_small(a, b);
	else
		radix_sort(a, b);
}
