/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:19:34 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 13:17:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * create_threads - Creates a thread for each philosopher.
 * @data: Pointer to the simulation data structure.
 * Return: 0 on success, 1 on failure.
 */
int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_life, &data->philosophers[i]) != 0)
			return (ft_printf("Error: Failed to create thread.\n"), 1);
		ft_printf("Thread %d created.\n", i + 1);
		i++;
	}
	return (0);
}

/**
 * join_threads - Waits for all philosopher threads to finish.
 * @data: Pointer to the simulation data structure.
 */
void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}
