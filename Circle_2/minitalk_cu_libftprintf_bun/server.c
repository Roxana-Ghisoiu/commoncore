/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:17:15 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/12/17 18:31:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Signal handler for receiving bits.
 * This function reconstructs characters bit by bit when receiving
 * SIGUSR1 (bit 0) and SIGUSR2 (bit 1). Once 8 bits are received,
 * the complete character is printed. A NULL character marks the
 * end of the message and a new line is printed.
 * @param sig The signal received (SIGUSR1 or SIGUSR2).
 */

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int				bit;
	static unsigned char	c;
	static pid_t			client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		bit = 0;
		c = 0;
		client_pid = info->si_pid;
	}
	c = c << 1;
	if (sig == SIGUSR2)
		c = c | 1;
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		bit = 0;
		c = 0;
	}
	if (kill(client_pid, SIGUSR2) == -1)
		write(2, "Error sending confirmation\n", 27);
}

/**
 * Main function for the server program.
 * The server prints its PID, waits for signals (SIGUSR1 and SIGUSR2),
 * and reconstructs characters bit by bit using a signal handler.
 * The program runs indefinitely until stopped.
 * @return int Always returns 0.
 */

int	main(void)
{
	struct sigaction	act;
	sigset_t			s;

	sigemptyset(&s);
	ft_printf("Server PID: %d\n", getpid());
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	act.sa_mask = s;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
