/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:24:39 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/20 19:54:19 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
  * @brief Main function to initialize and run the philosophers' simulation.
  *
  * @param argc Number of command-line arguments.
  * @param argv Array of command-line arguments.
  * @return int Returns 0 on successful execution, 1 on failure.
  */
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (ft_putendl_fd(WRONG_NUM_ARGS, 2), 1);
	if (check_valid_args(argv) == 1)
		return (1);
	if (open_semaphores(&data, ft_atoi(argv[1])) == 1)
		return (1);
	init_data(&data, argv);
	init_philosophers(&data);
	init_process(&data);
	wait_for_processes(&data);
	close_data(&data);
	return (0);
}



/**
 * @brief Checks if a given string represents a valid positive integer.
 *
 * @param str The string to check.
 * @return int Returns 1 if the string is not a valid number, 0 if valid.
 */
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Validates the command-line arguments.
 *
 * This function ensures that all arguments are valid positive integers.
 *
 * @param argv The array of command-line arguments.
 * @return int Returns 1 if an error is found, 0 if arguments are valid.
 */
int	check_valid_args(char *argv[])
{
	if (is_valid_number(argv[1]) || ft_atoi(argv[1]) < 1)
		return (ft_putendl_fd("Error: Invalid number of philosophers.", 2), 1);
	if (is_valid_number(argv[2]) || ft_atoi(argv[2]) < 1)
		return (ft_putendl_fd("Error: Invalid time_to_die.", 2), 1);
	if (is_valid_number(argv[3]) || ft_atoi(argv[3]) < 1)
		return (ft_putendl_fd("Error: Invalid time_to_eat.", 2), 1);
	if (is_valid_number(argv[4]) || ft_atoi(argv[4]) < 1)
		return (ft_putendl_fd("Error: Invalid time_to_sleep.", 2), 1);
	if (argv[5] && (is_valid_number(argv[5]) || ft_atoi(argv[5]) < 1))
		return (ft_putendl_fd
			("Err: Invalid nb_of_tms_each_philo_must_eat.", 2), 1);
	return (0);
}
