/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:28:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 10:41:07 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Allocates memory for philosophers and forks.
 * 
 * @param data Pointer to the simulation data structure.
 * @return int 0 if successful, 1 if allocation fails.
 */
static int	allocate_memory(t_data *data)
{
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->philosophers || !data->forks)
	{
		free(data->philosophers);
		free(data->forks);
		return (1);
	}
	return (0);
}

/**
 * @brief Initializes mutexes for forks and control structures.
 * 
 * @param data Pointer to the simulation data structure.
 * @return int 0 if successful, 1 if initialization fails.
 */

static int	init_mutexes(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		return (1);
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		return (1);
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		return (1);
	}
	return (0);
}

/**
 * @brief Initializes each philosopher with attributes and assigns forks.
 * 
 * @param data Pointer to the simulation data structure.
 */
static void	initialize_each_philosopher(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].times_eaten = 0;
		data->philosophers[i].eating = 0;
		data->philosophers[i].start_time = get_timestamp();
		data->philosophers[i].last_meal_time = get_timestamp();
		data->philosophers[i].left_fork = &data->forks[i];
		if (i == 0)
			data->philosophers[i].right_fork
				= &data->forks[data->num_philosophers - 1];
		else
			data->philosophers[i].right_fork = &data->forks[i - 1];
		data->philosophers[i].data = data;
		i++;
	}
}

/**
 * @brief Initializes the philosopher simulation.
 * 
 * Allocates memory, initializes mutexes, 
 * and prepares the philosopher structures.
 * 
 * @param data Pointer to the simulation data structure.
 * @return int 0 if successful, 1 if an error occurs.
 */

int	initialize_philosophers(t_data *data)
{
	if (allocate_memory(data))
	{
		return (1);
	}
	if (init_mutexes(data))
	{
		return (1);
	}
	data->start_time = get_timestamp();
	data->dead_flag = 0;
	initialize_each_philosopher(data);
	return (0);
}
