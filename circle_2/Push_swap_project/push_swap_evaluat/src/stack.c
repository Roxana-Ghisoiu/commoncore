/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:28:55 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 12:29:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Initializes an empty stack.
*/
t_stack	*stack_init(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->size = 0;
	return (stack);
}

/*
** Creates a new node with a given value.
*/
t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/*
** Pushes a new value onto the stack.
*/
void	stack_push(t_stack *stack, int value)
{
	t_node	*node;

	node = new_node(value);
	if (!node)
		return ;
	if (stack->top)
	{
		node->next = stack->top;
		stack->top->prev = node;
	}
	stack->top = node;
	stack->size++;
}

/*
** Pops the top value from the stack and returns it.
** Returns 0 if the stack is empty.
*/
int	stack_pop(t_stack *stack)
{
	t_node	*temp;
	int		value;

	if (!stack->top)
		return (0);
	temp = stack->top;
	value = temp->value;
	stack->top = temp->next;
	if (stack->top)
		stack->top->prev = NULL;
	free(temp);
	stack->size--;
	return (value);
}

/*
** Frees the entire stack.
*/
void	stack_free(t_stack *stack)
{
	t_node	*temp;

	if (!stack)
		return ;
	while (stack->top)
	{
		temp = stack->top;
		stack->top = stack->top->next;
		free(temp);
	}
	free(stack);
}
