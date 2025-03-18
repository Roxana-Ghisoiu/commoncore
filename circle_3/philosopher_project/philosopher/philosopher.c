/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:29:28 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 13:23:42 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * @brief Checks if the simulation is still active.
 * 
 * This function locks the dead_flag mutex and verifies
 * whether the simulation should continue.
 * 
 * @param data Pointer to the simulation data structure.
 * @return int 1 if the simulation is active, 0 otherwise.
 */
int	is_simulation_active(t_data *data)
{
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
 * @brief Locks both forks for the philosopher.
 * 
 * The philosopher must lock both the left and right fork
 * before they can eat.
 * 
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the simulation data structure.
 * @return int 1 if forks are locked successfully, 0 if the simulation stops.
 */
int	lock_forks(t_philosopher *philo, t_data *data)
{
	if (!is_simulation_active(data))
		return (0);
	printf("Philosopher %d waiting for left fork\n", philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("Philosopher %d took left fork\n", philo->id);
	print_status(data, philo->id, "has taken a fork");
	printf("Philosopher %d waiting for right fork\n", philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("Philosopher %d took right fork\n", philo->id);
	print_status(data, philo->id, "has taken a fork");
	return (1);
}

/**
 * @brief The philosopher eats and updates the last meal time.
 * 
 * The philosopher must acquire both forks, eat, update their
 * last meal timestamp, and then release the forks.
 * 
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the simulation data structure.
 * @return int 1 if the philosopher successfully eats, 0 if the simulation stops.
 */

int	eat(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(data, philo->id, "has taken a fork");
	if (data->num_philosophers == 1)
	{
		my_usleep(data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(data, philo->id, "has taken a fork");
	print_status(data, philo->id, "is eating");
	pthread_mutex_lock(&data->meal_lock);
	philo->last_meal_time = get_timestamp();
	philo->times_eaten++;
	pthread_mutex_unlock(&data->meal_lock);
	my_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

/**
 * @brief The philosopher sleeps and then starts thinking.
 * 
 * The philosopher follows the routine of sleeping for a
 * defined period and then thinking before the next meal.
 * 
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the simulation data structure.
 * @return int 1 if the philosopher continues, 0 if the simulation stops.
 */

int	sleep_and_think(t_philosopher *philo, t_data *data)
{
	if (!is_simulation_active(data))
		return (0);
	print_status(data, philo->id, "is sleeping");
	my_usleep(data->time_to_sleep);
	if (!is_simulation_active(data))
		return (0);
	print_status(data, philo->id, "is thinking");
	return (1);
}
