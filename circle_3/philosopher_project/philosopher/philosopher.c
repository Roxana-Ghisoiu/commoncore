/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:28:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/10 16:54:56 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(data, philo->id, "has taken a fork");
}

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

void	sleep_and_think(t_philosopher *philo, t_data *data)
{
	print_status(data, philo->id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	print_status(data, philo->id, "is thinking");
}

void	*philosopher_life(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = (t_data *)((char *)philo - offsetof(t_data, philosophers)
			+ philo->id * sizeof(t_philosopher));
	while (data->simulation_running)
	{
		eat(philo, data);
		if (data->num_times_to_eat != -1
			&& philo->times_eaten >= data->num_times_to_eat)
			break ;
		sleep_and_think(philo, data);
	}
	return (NULL);
}
