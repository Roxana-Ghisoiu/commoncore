/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:18:27 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/20 20:28:44 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
  * @brief Checks if a philosopher has died.
  * @param data Pointer to the main data structure.
  * @param i Index of the philosopher being checked.
  * @return int Returns 1 if a philosopher died, 0 otherwise.
  */
int	check_philosopher_death(t_data *data, int i)
{
	long long	current_time;

	current_time = get_time();
	if ((current_time - data->philosophers[i].last_meal_time)
		>= data->time_to_die)
	{
		sem_wait(data->write_lock);
		printf("%lld %d died\n", get_time()
			- data->start_time, data->philosophers[i].id);
		sem_post(data->dead_lock);
		return (1);
	}
	return (0);
}

/**
  * @brief Checks if all philosophers have finished their meals.
  *
  * @param data Pointer to the main data structure.
  * @return int Returns 1 if all philosophers are done, 0 otherwise.
  */

int	check_philosophers_done(t_data *data)
{
	int	i;
	int	philos_done;

	if (data->num_times_to_eat == -1)
		return (0);
	philos_done = 0;
	i = 0;
	while (i < data->num_philosophers)
	{
		if (data->philosophers[i].times_eaten
			>= data->num_times_to_eat)
			philos_done++;
		i++;
	}
	if (philos_done == data->num_philosophers)
	{
		sem_post(data->stop_lock);
		return (1);
	}
	return (0);
}

void	monitor_philosophers(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->num_philosophers)
		{
			if (check_philosopher_death(data, i))
			{
				sem_post(data->stop_lock);
				return ;
			}
		}
		if (check_philosophers_done(data))
			return ;
		usleep(1000);
	}
}
