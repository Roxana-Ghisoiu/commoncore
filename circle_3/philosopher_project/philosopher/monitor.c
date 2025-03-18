/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:38:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 13:04:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Monitors philosophers and stops the simulation if needed.
 * 
 * This function runs in a separate thread and checks periodically if
 * any philosopher has exceeded the time_to_die limit or if all have eaten.
 * 
 * @param arg Pointer to the main data structure.
 * @return NULL when execution ends.
 */

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_simulation_end(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			break ;
		}
		usleep(500);
	}
	pthread_exit(NULL);
}

/**
 * @brief Checks if all philosophers have eaten the required number of meals.
 * This function iterates through all philosophers and checks if they have 
 * reached the `num_times_to_eat` limit.
 * @param data Pointer to the simulation data structure.
 * @return int 1 if all philosophers have eaten enough, 0 otherwise.
 */
int	check_if_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (data->num_times_to_eat == -1)
		return (0);
	while (i < data->num_philosophers)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philosophers[i].times_eaten >= data->num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	if (finished_eating == data->num_philosophers)
		return (1);
	return (0);
}

/**
 * @brief Checks if any philosopher has died or if all have eaten.
 * 
 * @param data Pointer to the simulation data structure.
 * @return int 1 if simulation should stop, 0 otherwise.
 */

int	check_simulation_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (check_philosopher_dead(data, i))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
	}
	if (data->num_times_to_eat > 0 && check_if_all_ate(data))
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

/**
 * @brief Checks if a philosopher has died.
 * 
 * This function checks if the time since the last meal
 * exceeds the time_to_die threshold.
 * 
 * @param data Pointer to the simulation data structure.
 * @param i Index of the philosopher.
 * @return int 1 if the philosopher has died, 0 otherwise.
 */

int	check_philosopher_dead(t_data *data, int i)
{
	long	current_time;

	pthread_mutex_lock(&data->meal_lock);
	current_time = get_timestamp();
	if ((current_time - data->philosophers[i].last_meal_time)
		>= data->time_to_die)
	{
		pthread_mutex_unlock(&data->meal_lock);
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead_flag == 0)
		{
			data->dead_flag = 1;
			printf("%ld %d died\n", current_time - data->start_time,
				data->philosophers[i].id);
		}
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (0);
}
