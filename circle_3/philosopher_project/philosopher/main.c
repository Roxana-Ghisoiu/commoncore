/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:28:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 12:33:04 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Starts the philosopher and monitor threads.
 * @param data Pointer to the simulation data structure.
 * @return 0 on success, 1 on failure.
 */
int	start_threads(t_data *data)
{
	int	i;

	if (pthread_create(&data->monitor_thread, NULL,
			(void *)monitor, data) != 0)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				(void *)philosopher_routine, &data->philosophers[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Main function for the philosopher simulation.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status.
 */

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data))
		return (1);
	if (initialize_philosophers(&data))
		return (1);
	if (create_threads(&data))
		return (1);
	cleanup(&data);
	return (0);
}
