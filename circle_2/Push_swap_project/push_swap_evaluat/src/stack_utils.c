/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:11:22 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/25 12:11:37 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Finds the last node in the stack.
 */
t_node	*find_last_node(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top)
		return (NULL);
	current = stack->top;
	while (current->next)
		current = current->next;
	return (current);
}

/**
 * @brief Finds the smallest node in the stack.
 */
t_node	*find_smallest(t_stack *stack)
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
 * Fills the stack with parsed integer values.
 */
void	stack_fill(t_stack *a, char **argv, bool is_split)
{
	int		i;
	long	value;
	t_node	*current;

	i = 0;
	while (argv[i])
	{
		value = ft_atol(argv[i]);
		if (value == 3000000000)
			error_free(a, argv, is_split);
		current = a->top;
		while (current)
		{
			if (current->value == (int)value)
				error_free(a, argv, is_split);
			current = current->next;
		}
		stack_push(a, (int)value);
		i++;
	}
	if (is_split)
		free_matrix(argv);
}

/**
 * @brief Returns the number of elements in the stack.
 */
int	stack_size(t_stack *a)
{
	int		count;
	t_node	*current;

	if (!a || !a->top)
		return (0);
	count = 0;
	current = a->top;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Checks if the stack is sorted in ascending order.
 */
int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}
