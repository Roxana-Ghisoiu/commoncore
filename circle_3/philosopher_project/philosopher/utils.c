/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:07:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 13:30:55 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Prints the status of a philosopher.
 *
 * This function locks the print mutex, checks if the simulation is active,
 * and then prints the philosopher's status.
 *
 * @param data Pointer to the simulation data.
 * @param id The ID of the philosopher.
 * @param status The status message to print.
 */

void	print_status(t_data *data, int id, const char *status)
{
	long	timestamp;

	if (!data || !status)
		return ;
	pthread_mutex_lock(&data->write_lock);
	if (data->dead_flag == 0)
	{
		timestamp = get_timestamp() - data->start_time;
		printf("%ld %d %s\n", timestamp, id, status);
		fflush(stdout);
	}
	pthread_mutex_unlock(&data->write_lock);
}

/**
 * @brief Gets the current timestamp in milliseconds.
 *
 * Uses `gettimeofday()` to retrieve the current time and converts it to
 * milliseconds since the epoch.
 *
 * @return The current timestamp in milliseconds.
 */
long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Sleeps for a specified amount of milliseconds.
 *
 * Uses `gettimeofday()` to track elapsed time and `usleep()` to wait
 * in short intervals until the total requested time has passed.
 *
 * @param time The time in milliseconds to sleep.
 */
void	my_usleep(long time)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000
			+ (current.tv_usec - start.tv_usec) / 1000;
		if (elapsed >= time)
			break ;
		usleep(100);
	}
}

/**
 * @brief Determines if the philosopher should continue.
 * 
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the simulation data.
 * @return int 1 if the philosopher should continue, 0 otherwise.
 */
int	should_continue(t_philosopher *philo, t_data *data)
{
	(void)philo;
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_flag)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (1);
}

/**
 * @brief Checks if the philosopher should stop execution.
 *
 * This function locks the dead_flag mutex and checks
 * if the simulation has ended.
 *
 * @param philo Pointer to the philosopher structure.
 * @return 1 if the simulation should stop, 0 otherwise.
 */

int	should_stop(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}
