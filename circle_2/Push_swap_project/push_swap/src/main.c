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
 * @brief Main function for push_swap
 */

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		*arr;
	int		size;
	int		i;

	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (0);
	arr = parse_args(argc, argv, &size);
	if (!arr)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (size == 1)
	{
		free(arr);
		return (0);
	}
	a = stack_init();
	b = stack_init();
	if (!a || !b)
		return (1);
	i = size -1;
	while (i >= 0)
	{
		stack_push(a, arr[i]);
		i--;
	}

	if (!is_sorted(a))
		push_swap(a, b);

	free(arr);
	stack_free(a);
	stack_free(b);
	return (0);
}
