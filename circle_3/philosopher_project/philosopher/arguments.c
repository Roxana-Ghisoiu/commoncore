/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:52:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 17:54:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (ft_printf("Error: Incorrect number of arguments.\n"), 1);
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (ft_printf("Error: Args must be positive numbers.\n"), 1);
		i++;
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (check_arguments(argc, argv))
		return (1);
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_times_to_eat = ft_atoi(argv[5]);
	else
		data->num_times_to_eat = -1;
	if (data->num_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->num_times_to_eat <= 0))
		return (ft_printf("Error: Args must be positive numbers > 0.\n"), 1);
	return (0);
}
