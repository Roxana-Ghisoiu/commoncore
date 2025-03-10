/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:43:25 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 12:43:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Rotates stack a (shifts all elements up, first becomes last).
 */
void	ra(t_stack *a)
{
	t_node	*first;
	t_node	*last;

	if (!a || stack_size(a) < 2)
		return ;
	first = a->top;
	last = a->top;
	while (last->next)
		last = last->next;
	a->top = first->next;
	a->top->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	ft_printf("ra\n");
}

/**
 * @brief Rotates stack b (shifts all elements up, first becomes last).
 */
void	rb(t_stack *b)
{
	t_node	*first;
	t_node	*last;

	if (!b || stack_size(b) < 2)
		return ;
	first = b->top;
	last = b->top;
	while (last->next)
		last = last->next;
	b->top = first->next;
	b->top->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	ft_printf("rb\n");
}

/**
 * @brief Performs ra and rb at the same time.
 */
void	rr(t_stack *a, t_stack *b)
{
	ra(a);
	rb(b);
	ft_printf("rr\n");
}
