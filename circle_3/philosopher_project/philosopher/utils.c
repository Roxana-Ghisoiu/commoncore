/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:07:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 19:14:44 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * print_status - Prints a philosopher's status safely.
 * @data: Pointer to simulation data.
 * @id: Philosopher ID.
 * @status: The status message.
 */
void	print_status(t_data *data, int id, const char *status)
{
	long	timestamp;

	if (!data || !status || !data->simulation_running)
		return ;
	timestamp = get_timestamp() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	if (data->simulation_running)
		ft_printf("%ld %d %s\n", timestamp, id, status);
	pthread_mutex_unlock(&data->print_mutex);
}

/**
 * get_timestamp - Returns the current time in milliseconds.
 * Return: The timestamp in milliseconds since the program started.
 */
long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
