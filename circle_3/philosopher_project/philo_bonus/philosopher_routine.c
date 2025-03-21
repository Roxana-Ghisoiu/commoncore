/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:14:01 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/20 20:05:56 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
  * @brief Handles the eating process of a philosopher.
  * @param philo Pointer to the philosopher's data.
  */
void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	sem_wait(philo->data->write_lock);
	printf("%lld %d is eating\n", get_time()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->write_lock);
	philo->last_meal_time = get_time();
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->times_eaten++;
}


/**
 * @brief Handles the sleeping process of a philosopher.
 *
 * @param philo Pointer to the philosopher's data.
 */
void	dream(t_philo *philo)
{
	sem_wait(philo->data->write_lock);
	printf("%lld %d is sleeping\n", get_time()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->write_lock);
	usleep(philo->data->time_to_sleep * 1000);
}

/**
 * @brief Handles the thinking process of a philosopher.
 *
 * @param philo Pointer to the philosopher's data.
 */
void	think(t_philo *philo)
{
	sem_wait(philo->data->write_lock);
	printf("%lld %d is thinking\n", get_time()
		- philo->data->start_time, philo->id);
	sem_post(philo->data->write_lock);
}

/**
  * @brief Main routine for each philosopher process.
  * @param philo Pointer to the philosopher's data.
  */
void	philosopher_routine(t_philo *philo)
{
	printf("%lld %d has taken a fork\n", get_time()
		- philo->data->start_time, philo->id);
	fflush(stdout);
	if (philo->data->num_philosophers == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		sem_wait(philo->data->write_lock);
		printf("%lld %d died\n", get_time()
			- philo->data->start_time, philo->id);
		sem_post(philo->data->stop_lock);
		exit(0);
	}
	while (1)
	{
		eat(philo);
		if (philo->data->num_times_to_eat != -1
			&& philo->times_eaten >= philo->data->num_times_to_eat)
		{
			sem_post(philo->data->meal_lock);
			exit(0);
		}
		dream(philo);
		think(philo);
	}
	exit(0);
}
