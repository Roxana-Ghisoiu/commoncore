/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:18:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 12:18:46 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * cleanup_resources - Frees memory and destroys mutexes.
 * @data: Pointer to the simulation data structure.
 */
void	cleanup_resources(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philosophers);
}
