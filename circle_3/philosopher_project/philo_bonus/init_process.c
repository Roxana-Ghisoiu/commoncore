/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:25:09 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/20 20:38:04 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
  * @brief Kills all philosopher processes.
  *
  * @param data Pointer to the main data structure.
  */
void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		kill(data->philosophers[i].pid, SIGKILL);
		i++;
	}
	close_semaphores(data);
}

/**
  * @brief Creates philosopher processes.
  *
  * @param data Pointer to the main data structure.
  * @return int Returns 0 on success, 1 on failure.
  */
int	create_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
		{
			kill_all(data);
			return (ft_putendl_fd("Error: Fork failed", 2), 1);
		}
		if (data->philosophers[i].pid == 0)
			philosopher_routine(&data->philosophers[i]);
		i++;
	}
	return (0);
}

/**
  * @brief Creates the monitor process.
  *
  * @param data Pointer to the main data structure.
  * @return int Returns 0 on success, 1 on failure.
  */

int	create_monitor(t_data *data)
{
	pid_t	monitor_pid;

	monitor_pid = fork();
	if (monitor_pid < 0)
	{
		kill_all(data);
		return (ft_putendl_fd("Error: Fork failed for monitor", 2), 1);
	}
	if (monitor_pid == 0)
		monitor_philosophers(data);
	return (0);
}

/**
  * @brief Initializes philosopher and monitor processes.
  *
  * @param data Pointer to the main data structure.
  * @return int Returns 0 on success, 1 on failure.
  */
int	init_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid < 0)
		{
			kill_all(data);
			return (ft_putendl_fd("Error: Fork failed", 2), 1);
		}
		if (data->philosophers[i].pid == 0)
			philosopher_routine(&data->philosophers[i]);
		i++;
	}
	usleep(500);
	return (0);
}


/**
 * @brief Waits for all philosopher processes to finish.
 *
 * @param data Pointer to the main data structure.
 */
void	wait_for_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_philosophers)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
