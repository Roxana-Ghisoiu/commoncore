/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:02 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/24 12:13:09 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
/**
 * Main function of push_swap.
 */
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		*arr;
	int		size;
	int		i;

	if (argc < 2 || (argc == 2 && !argv[1][0]))
		return (0);
	arr = parse_args(argc, argv, &size);
	if (!arr)
		return (write(2, "Error\n", 6), 1);
	if (size == 1)
		return (free(arr), 0);
	a = stack_init();
	b = stack_init();
	if (!a || !b)
		return (free(arr), 1);
	i = size;
	while (--i >= 0)
		stack_push(a, arr[i]);
	if (!is_sorted(a))
		push_swap(a, b);
	return (free(arr), stack_free(a), stack_free(b), 0);
}
