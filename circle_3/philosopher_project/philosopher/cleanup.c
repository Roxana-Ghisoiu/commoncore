/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:18:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 12:36:03 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Frees allocated memory and destroys mutexes.
 *
 * This function ensures proper cleanup of allocated resources, including:
 * - Destroying all mutexes.
 * - Freeing memory allocated for forks and philosophers.
 *
 * @param data Pointer to the simulation data structure.
 */
void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->forks);
	free(data->philosophers);
}

/**
 * @brief Calculates the length of a string.
 * 
 * @param str The input string.
 * @return int The length of the string.
 */
int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
