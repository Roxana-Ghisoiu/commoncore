/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:08:29 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 12:08:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
#include <stdbool.h>
# include <unistd.h>
# include "libft.h" 

/* Node structure representing a stack element */
typedef struct s_node
{
    int             value;
    int             index;
    struct s_node   *next;
    struct s_node   *prev;
}                   t_node;

/* Stack structure */
typedef struct s_stack
{
	t_node	*top;
	int		size;
}			t_stack;

/* Prototip for function push_swap.c*/
void	push_swap(t_stack *a, t_stack *b);

/* Parsing functions from parse_args.c */
int		is_number(char *str);
int		is_valid_int(char *str);
int		has_duplicates(int *arr, int size);
int		*parse_args(int argc, char **argv, int *size);

/* Stack functions from stack.c */
t_stack	*stack_init(void);
t_node	*new_node(int value);
void	stack_push(t_stack *stack, int value);
int		stack_pop(t_stack *stack);
void	stack_free(t_stack *stack);

/* Operations from operations.c */
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

/* Rotation operations from rotate.c */
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);

/* Reverse rotation operations from reverse_rotate.c */
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/* Sorting functions from sort_small.c */
t_node	*find_min(t_stack *stack);
void	sort_three(t_stack *a);
void	sort_small(t_stack *a, t_stack *b);

/* Radix sort functions from sort_radix.c */
void	sort_array(int *arr, int size);
void	index_stack(t_stack *a, int *arr, int size);
void	prepare_stack_for_radix(t_stack *a);
void execute_radix_sort(t_stack *a, t_stack *b, int max_bits, int initial_size);
void radix_sort(t_stack *a, t_stack *b);

/* Checker functions from checker.c */
void	print_stack(t_stack *stack);

/* Prototip for function stack_utils.c*/
t_node *find_last_node(t_stack *stack);
t_node *find_smallest(t_stack *stack);
void stack_fill(t_stack *a, char **argv, bool is_split);
int stack_size(t_stack *a);
int	is_sorted(t_stack *stack);

/* Prototip for function error_free.c*/
void free_matrix(char **argv);
void free_stack(t_stack *stack);
void error_free(t_stack *a, char **argv, bool flag_argc_2);

/* Prototip for function ft_atol.c*/
long	ft_atol(const char *str);

#endif
