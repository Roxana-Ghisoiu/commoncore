/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:44:30 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 19:08:42 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * init_mutexes - Initializes all mutexes for forks and printing.
 * @data: Pointer to the program's main data structure.
 * Return: 0 if successful, 1 if an error occurs.
 */
static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (ft_printf("Error: Mutex initialization failed.\n"), 1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i]);
		return (ft_printf("Error: Print mutex initialization failed.\n"), 1);
	}
	return (0);
}

/**
 * assign_forks - Assigns forks to each philosopher.
 * @data: Pointer to the program's main data structure.
 */
static void	assign_forks(t_data *data)
{
	int	i;
	int	index;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].times_eaten = 0;
		data->philosophers[i].last_meal_time = data->start_time;
		data->philosophers[i].left_fork = &data->forks[i];
		index = (i + 1) % data->num_philosophers;
		if (data->num_philosophers > 1)
			data->philosophers[i].right_fork = &data->forks[index];
		else
			data->philosophers[i].right_fork = NULL;
		data->philosophers[i].data = data;
		i++;
	}
}

/**
 * initialize_philosophers - Allocates memory and initializes philosophers.
 * @data: Pointer to the program's main data structure.
 * Return: 0 if successful, 1 if an error occurs.
 */
int	initialize_philosophers(t_data *data)
{
	if (data->num_philosophers <= 0)
		return (ft_printf("Error: At least 1 philosopher required.\n"), 1);
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->philosophers || !data->forks)
	{
		free(data->philosophers);
		free(data->forks);
		return (ft_printf("Error: Memory allocation failed.\n"), 1);
	}
	ft_bzero(data->philosophers, sizeof(t_philosopher)
		* data->num_philosophers);
	if (init_mutexes(data))
		return (1);
	data->start_time = get_timestamp();
	data->simulation_running = 1;
	assign_forks(data);
	return (0);
}
