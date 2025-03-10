/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:32:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/10 16:59:42 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include "libft.h"

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				times_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	long			start_time;
	int				simulation_running;
	pthread_mutex_t	print_mutex;
}	t_data;

int		parse_arguments(int argc, char **argv, t_data *data);
void	initialize_philosophers(t_data *data);
void	create_threads(t_data *data);
void	join_threads(t_data *data);
void	cleanup_resources(t_data *data);
void	print_status(t_data *data, int id, const char *status);
long	get_timestamp(void);
void	*philosopher_life(void *arg);

#endif
