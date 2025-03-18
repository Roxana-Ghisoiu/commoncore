/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:32:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/18 12:58:11 by rghisoiu         ###   ########.fr       */
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
# include <string.h>

/* -------------------- STRUCTURES -------------------- */

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				eating;
	int				times_eaten;
	long			last_meal_time;
	size_t			start_time;
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
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_t		monitor_thread;
}	t_data;

/* ------------ FUNCTIONS DEFINED IN arguments.c ---------- */

int		parse_arguments(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);

/* ------------ FUNCTIONS DEFINED IN init.c --------------- */

int		initialize_philosophers(t_data *data);

/* ------------ FUNCTIONS DEFINED IN philosopher.c -------- */

int		is_simulation_active(t_data *data);
int		lock_forks(t_philosopher *philo, t_data *data);
int		eat(t_philosopher *philo, t_data *data);
int		sleep_and_think(t_philosopher *philo, t_data *data);

/* ------------ FUNCTIONS DEFINED IN threads.c ------------ */
int		create_monitor_thread(t_data *data, pthread_t *observer);
int		create_philosopher_threads(t_data *data);
int		join_threads(t_data *data, pthread_t observer);
int		create_threads(t_data *data);
void	*philosopher_routine(void *pointer);

/* ------------ FUNCTIONS DEFINED IN cleanup.c ------------ */

void	cleanup(t_data *data);
int		ft_strlen(char *str);

/* ------------ FUNCTIONS DEFINED IN utils.c -------------- */

void	print_status(t_data *data, int id, const char *status);
long	get_timestamp(void);
void	my_usleep(long time);
int		should_stop(t_philosopher *philo);

/* ------------ FUNCTIONS DEFINED IN main.c -------- */
int		start_threads(t_data *data);

/* ------------ FUNCTIONS DEFINED IN monitor.c -------- */
void	*monitor(void *arg);
int		check_simulation_end(t_data *data);
int		check_if_all_ate(t_data *data);
int		check_philosopher_dead(t_data *data, int i);
#endif