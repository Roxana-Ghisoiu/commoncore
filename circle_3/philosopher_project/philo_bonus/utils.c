/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:50:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/20 18:18:08 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Converts a string to an integer.
 *
 * @param str The string to convert.
 * @return int The converted integer.
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/**
 * @brief Writes a string followed by a newline to a file descriptor.
 *
 * @param str The string to write.
 * @param fd The file descriptor.
 */
void	ft_putendl_fd(char *str, int fd)
{
	if (!str)
		return ;
	while (*str)
		write(fd, str++, 1);
	write(fd, "\n", 1);
}

/**
 * @brief A more precise usleep implementation.
 *
 * @param milliseconds The time to sleep in milliseconds.
 */
void	ft_usleep(long milliseconds)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < milliseconds)
		usleep(100);
}

/**
 * @brief Checks if a string contains only digits.
 *
 * @param str The string to check.
 * @return int Returns 1 if only digits, 0 otherwise.
 */
int	has_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
