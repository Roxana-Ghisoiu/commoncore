/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:00:06 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 13:02:02 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Finds the smallest node in the stack.
 */
t_node	*find_min(t_stack *stack)
{
	t_node	*current;
	t_node	*min;

	if (!stack || !stack->top)
		return (NULL);
	current = stack->top;
	min = current;
	while (current)
	{
		if (current->value < min->value)
			min = current;
		current = current->next;
	}
	return (min);
}

/**
 * @brief Sorts 3 numbers in stack a using the least number of moves.
 */
void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (stack_size(a) != 3)
		return ;
	first = a->top->value;
	second = a->top->next->value;
	third = a->top->next->next->value;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}


/**
 * @brief Sorts a stack of 4 or 5 numbers.
 */
void	sort_small(t_stack *a, t_stack *b)
{
	t_node	*min;

	if (stack_size(a) == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a);
		return ;
	}
	if (stack_size(a) == 3)
	{
		sort_three(a);
		return ;
	}
	while (stack_size(a) > 3)
	{
		min = find_min(a);
		while (a->top != min)
		{
			if (min == a->top->next)
				sa(a);
			else
				rra(a);
		}
		pb(a, b);
	}
	sort_three(a);
	while (stack_size(b) > 0)
		pa(a, b);
}
