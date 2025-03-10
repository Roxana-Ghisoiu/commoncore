/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:01:42 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/12/17 18:09:20 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef SIGNAL_ONE
#  define SIGNAL_ONE SIGUSR2
# endif

# ifndef SIGNAL_ZERO
#  define SIGNAL_ZERO SIGUSR1
# endif

# include "LibftPrintf/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Prototipurile funcțiilor */

/*server*/
void	signal_handler(int sig, siginfo_t *info, void *context);
void	process_bit(int sig, pid_t client_pid);

/*client*/

void	ft_response(int signum);
void	send_bit(int pid, int bit);
void	send_char(int pid, char c);
void	send_str(int pid, char *str);

#endif
