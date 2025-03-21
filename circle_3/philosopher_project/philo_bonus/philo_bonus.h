/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:34:47 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/20 17:58:40 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>

# define WRONG_NUM_ARGS "Error: Wrong number of arguments."

/*----------Structures------------*/

typedef struct s_data	t_data;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			eating;
	int			times_eaten;
	long long	last_meal_time;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int			num_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_times_to_eat;
	long long	start_time;
	t_philo		*philosophers;
	sem_t		*forks;
	sem_t		*dead_lock;
	sem_t		*meal_lock;
	sem_t		*write_lock;
	sem_t		*stop_lock;
	pid_t		monitor_pid;
}	t_data;

/*----------Function Prototypes for main.c------------*/
int			main(int argc, char *argv[]);
int			check_valid_args(char *argv[]);

/*----------Function Prototypes for open_close_semaphores.c------------*/
int			open_semaphores(t_data *data, int num_philosophers);
void		close_semaphores(t_data *data);
void		close_data(t_data *data);

/*----------Function Prototypes for init_process.c------------*/
void		kill_all(t_data *data);
int			create_philosophers(t_data *data);
int			create_monitor(t_data *data);
int			init_process(t_data *data);
void		wait_for_processes(t_data *data);

/*----------Function Prototypes for philosopher_routine.c------------*/
void		eat(t_philo *philo);
void		think(t_philo *philo);
void		dream(t_philo *philo);
void		philosopher_routine(t_philo *philo);

/*----------Function Prototypes for monitor_philosopher.c------------*/
int			check_philosopher_death(t_data *data, int i);
int			check_philosophers_done(t_data *data);
void		monitor_philosophers(t_data *data);

/*----------Function Prototypes for utils.c------------*/
int			ft_atoi(const char *str);
void		ft_putendl_fd(char *str, int fd);
void		ft_usleep(long milliseconds);
int			has_only_digits(char *str);
long long	get_time(void);

/*----------Function Prototypes for init_data.c------------*/
void		init_data(t_data *data, char *argv[]);
void		init_philosophers(t_data *data);

#endif
