/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:32:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 18:52:46 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include "LibftPrintf/libft.h"  // Includes useful functions from libft

/* -------------------- STRUCTURES -------------------- */

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				times_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
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

/* ------------ FUNCTIONS DEFINED IN arguments.c ---------- */

// Parses and validates command-line arguments
int		parse_arguments(int argc, char **argv, t_data *data);

/* ------------- FUNCTIONS DEFINED IN philosopher.c ------ */

// Initializes philosophers' structures and fork mutexes
int		initialize_philosophers(t_data *data);

// The main function for each philosopher (executed in threads)
void	*philosopher_life(void *arg);

/* ----------- FUNCTIONS DEFINED IN threads.c --------- */

// Creates threads for each philosopher
int		create_threads(t_data *data);

// Waits for all philosopher threads to finish
void	join_threads(t_data *data);

/* ---------- FUNCTIONS DEFINED IN cleanup.c ---------- */

// Cleans up resources (mutexes and allocated memory)
void	cleanup_resources(t_data *data);

/* ----------- AUXILIARY FUNCTIONS (DEFINED IN utils.c) ------- */

// Prints the philosopher's status in a synchronized way
void	print_status(t_data *data, int id, const char *status);

// Returns the current timestamp in milliseconds
long	get_timestamp(void);
void	my_usleep(long time);

#endif
