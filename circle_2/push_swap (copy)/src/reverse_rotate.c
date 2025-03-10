/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:44:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 12:44:54 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Reverse rotates stack a (shifts all elements down, last becomes first).
 */
void	rra(t_stack *a)
{
	t_node	*last;

	if (!a || stack_size(a) < 2)
		return ;
	last = a->top;
	while (last->next)
		last = last->next;
	if (last->prev)
		last->prev->next = NULL;
	last->prev = NULL;
	last->next = a->top;
	a->top->prev = last;
	a->top = last;
	ft_printf("rra\n");
}

/**
 * @brief Reverse rotates stack b (shifts all elements down, last becomes first).
 */
void	rrb(t_stack *b)
{
	t_node	*last;

	if (!b || stack_size(b) < 2)
		return ;
	last = b->top;
	while (last->next)
		last = last->next;
	if (last->prev)
		last->prev->next = NULL;
	last->prev = NULL;
	last->next = b->top;
	b->top->prev = last;
	b->top = last;
	ft_printf("rrb\n");
}

/**
 * @brief Performs rra and rrb at the same time.
 */
void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rrb(b);
	ft_printf("rrr\n");
}
