/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:28:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/11 14:33:52 by rghisoiu         ###   ########.fr       */
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

#include "philosopher.h"

int	initialize_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->philosophers || !data->forks)
		return (ft_printf("Error: Memory allocation failed.\n"), 1);
	i = 0;
	while (i < data->num_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].times_eaten = 0;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		i++;
	}
	return (0);
}
