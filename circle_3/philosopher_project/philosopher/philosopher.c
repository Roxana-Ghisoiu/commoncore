/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:28:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 19:15:42 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * take_forks - Philosopher takes both forks (mutex lock).
 * @philo: Pointer to the philosopher structure.
 */
void	take_forks(t_philosopher *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(data, philo->id, "has taken a fork");
	}
}

/**
 * eat - Philosopher eats and updates last meal time.
 * @philo: Pointer to the philosopher structure.
 */
void	eat(t_philosopher *philo, t_data *data)
{
	take_forks(philo, data);
	print_status(data, philo->id, "is eating");
	philo->last_meal_time = get_timestamp();
	philo->times_eaten++;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/**
 * sleep_and_think - Philosopher sleeps, then starts thinking.
 * @philo: Pointer to the philosopher structure.
 */
void	sleep_and_think(t_philosopher *philo, t_data *data)
{
	print_status(data, philo->id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	print_status(data, philo->id, "is thinking");
}

/**
 * should_continue - Checks if the philosopher should keep running.
 * @philo: Pointer to the philosopher structure.
 * @data: Pointer to the simulation data structure.
 * Return: 1 if should continue, 0 otherwise.
 */
int	should_continue(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!data->simulation_running
		|| (data->num_times_to_eat > 0
			&& philo->times_eaten >= data->num_times_to_eat))
	{
		pthread_mutex_unlock(&data->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->print_mutex);
	return (1);
}

/**
 * philosopher_life - Main routine for each philosopher thread.
 * @arg: Pointer to the philosopher structure.
 * Return: NULL when thread execution ends.
 */
void	*philosopher_life(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	ft_printf("DEBUG: Încep philosopher_life...\n");
	philo = (t_philosopher *)arg;
	if (!philo)
	{
		ft_printf("ERROR: philo este NULL!\n");
		return (NULL);
	}
	data = philo->data;
	if (!data)
	{
		ft_printf("ERROR: data este NULL în philosopher_life!\n");
		return (NULL);
	}
	ft_printf("DEBUG: Philosopher %d a început viața.\n", philo->id);
	return (NULL);
}
