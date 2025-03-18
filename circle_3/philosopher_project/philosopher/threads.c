/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:19:34 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 12:49:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Creates the monitor thread.
 * @param data Pointer to the main data structure.
 * @param observer Pointer to monitor thread.
 * @return int 0 on success, 1 on failure.
 */
int	create_monitor_thread(t_data *data, pthread_t *observer)
{
	if (pthread_create(observer, NULL, &monitor, data) != 0)
		return (1);
	return (0);
}

/**
 * @brief Creates all philosopher threads.
 * @param data Pointer to the main data structure.
 * @return int 0 on success, 1 on failure.
 */
int	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Joins all philosopher and monitor threads.
 * @param data Pointer to the main data structure.
 * @param observer Monitor thread.
 * @return int 0 on success, 1 on failure.
 */
int	join_threads(t_data *data, pthread_t observer)
{
	int	i;

	if (pthread_join(observer, NULL) != 0)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Main function to create and manage threads.
 * @param data Pointer to the main data structure.
 * @return int 0 on success, 1 on failure.
 */
int	create_threads(t_data *data)
{
	pthread_t	observer;

	if (create_monitor_thread(data, &observer))
		return (1);
	if (create_philosopher_threads(data))
		return (1);
	if (join_threads(data, observer))
		return (1);
	return (0);
}

/**
 * @brief Routine executed by each philosopher thread.
 * Each philosopher alternates between eating, sleeping, and thinking,
 * until the simulation is stopped.
 * @param pointer Pointer to the philosopher structure.
 * @return NULL when execution ends.
 */
void	*philosopher_routine(void *pointer)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)pointer;
	if (philo->id % 2 == 0)
		my_usleep(1);
	while (!should_stop(philo))
	{
		if (!eat(philo, philo->data))
			break ;
		if (!sleep_and_think(philo, philo->data))
			break ;
	}
	return (NULL);
}
