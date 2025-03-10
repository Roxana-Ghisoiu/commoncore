/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:35:10 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 12:35:54 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Swaps the first two elements of stack a.
 */
void	sa(t_stack *a)
{
	t_node	*first;
	t_node	*second;

	if (!a || stack_size(a) < 2)
		return ;
	first = a->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	a->top = second;
	ft_printf("sa\n");
}

/**
 * @brief Swaps the first two elements of stack b.
 */
void	sb(t_stack *b)
{
	t_node	*first;
	t_node	*second;

	if (!b || stack_size(b) < 2)
		return ;
	first = b->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	b->top = second;
	ft_printf("sb\n");
}

/**
 * @brief Performs sa and sb at the same time.
 */
void	ss(t_stack *a, t_stack *b)
{
	sa(a);
	sb(b);
	ft_printf("ss\n");
}

/**
 * @brief Pushes the first element from stack b to stack a.
 */
void	pa(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!b || !b->top)
		return ;
	temp = b->top;
	b->top = temp->next;
	if (b->top)
		b->top->prev = NULL;
	temp->next = a->top;
	if (a->top)
		a->top->prev = temp;
	a->top = temp;
	a->size++;
	b->size--;
	ft_printf("pa\n");
}

/**
 * @brief Pushes the first element from stack a to stack b.
 */
void	pb(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!a || !a->top)
		return ;
	temp = a->top;
	a->top = temp->next;
	if (a->top)
		a->top->prev = NULL;
	temp->next = b->top;
	if (b->top)
		b->top->prev = temp;
	b->top = temp;
	a->size--;
	b->size++;
	ft_printf("pb\n");
}
