/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:06:48 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 13:05:19 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Converts a string to an integer, handling invalid input.
 * 
 * This function replicates the behavior of `atoi`, ensuring only valid numbers
 * are converted.
 * 
 * @param str The string to convert.
 * @return int The converted number, or -1 if invalid.
 */
int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX || result < INT_MIN)
			return (-1);
		i++;
	}
	return ((int)(sign * result));
}

/**
 * @brief Checks if all arguments are valid positive numbers.
 * 
 * Iterates through each argument to ensure they contain only digits.
 * 
 * @param argc The number of arguments.
 * @param argv The argument array.
 * @return int 0 if valid, 1 if an error occurs.
 */
static int	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Incorrect number of arguments.\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Arguments must be positive numbers.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Validates philosopher constraints.
 * 
 * Ensures philosophers count is between 1 and 300, 
 * and timings are at least 60ms.
 * 
 * @param data Pointer to the main data structure.
 * @param argc Argument count.
 * @return int 0 if valid, 1 if an error occurs.
 */
static int	validate_constraints(t_data *data, int argc)
{
	if (data->num_philosophers > 300 || data->num_philosophers <= 0)
	{
		printf("Error: Invalid number of philosophers (1-300).\n");
		return (1);
	}
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
	{
		printf("Error: Timings must be at least 60ms.\n");
		return (1);
	}
	if (argc == 6 && data->num_times_to_eat <= 0)
	{
		printf("Error: num_times_to_eat must be > 0.\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Parses and validates command-line arguments.
 * 
 * Populates the `t_data` structure with valid arguments.
 * 
 * @param argc Number of arguments.
 * @param argv Array of argument strings.
 * @param data Pointer to the main data structure.
 * @return int 0 if successful, 1 if an error occurs.
 */
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
	return (validate_constraints(data, argc));
}
