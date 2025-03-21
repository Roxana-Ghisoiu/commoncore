/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_semaphores.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:53:08 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/20 20:44:20 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
  * @brief Closes and unlinks all semaphores.
  *
  * @param data Pointer to the main data structure.
  */

void	close_semaphores(t_data *data)
{
	static const char	*names[] = {
		"/forks",
		"/philo_write",
		"/philo_dead",
		"/philo_meal",
		"/philo_stop"
	};
	sem_t				*semaphores[5];
	int					i;

	semaphores[0] = data->forks;
	semaphores[1] = data->write_lock;
	semaphores[2] = data->dead_lock;
	semaphores[3] = data->meal_lock;
	semaphores[4] = data->stop_lock;
	i = 0;
	while (i < 5)
	{
		if (semaphores[i])
		{
			sem_close(semaphores[i]);
			sem_unlink(names[i]);
		}
		i++;
	}
}

/**
  * @brief Opens and initializes all required semaphores.
  *
  * @param data Pointer to the main data structure.
  * @param num_philosophers Number of philosophers (needed for fork semaphore).
  * @return int Returns 0 on success, 1 on failure.
  */
int	open_semaphores(t_data *data, int num_philosophers)
{
	sem_unlink("/forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_dead");
	sem_unlink("/philo_meal");
	sem_unlink("/philo_stop");
	data->forks = sem_open("/forks",
			O_CREAT | O_EXCL, 0644, num_philosophers);
	data->write_lock = sem_open("/philo_write", O_CREAT | O_EXCL, 0644, 1);
	data->dead_lock = sem_open("/philo_dead", O_CREAT | O_EXCL, 0644, 0);
	data->meal_lock = sem_open("/philo_meal", O_CREAT | O_EXCL, 0644, 1);
	data->stop_lock = sem_open("/philo_stop", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == SEM_FAILED
		|| data->write_lock == SEM_FAILED
		|| data->dead_lock == SEM_FAILED || data->meal_lock == SEM_FAILED
		|| data->stop_lock == SEM_FAILED)
	{
		ft_putendl_fd("Error: Failed to open semaphores", 2);
		close_semaphores(data);
		return (1);
	}
	return (0);
}

/**
 * @brief Closes and cleans up resources.
 *
 * @param data Pointer to the main data structure.
 */
void	close_data(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->dead_lock)
		sem_close(data->dead_lock);
	if (data->meal_lock)
		sem_close(data->meal_lock);
	if (data->write_lock)
		sem_close(data->write_lock);
	if (data->stop_lock)
		sem_close(data->stop_lock);
	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
}
