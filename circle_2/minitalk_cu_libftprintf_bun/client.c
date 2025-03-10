/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:33:42 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/12/17 18:36:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Signal handler to acknowledge that a signal has been received.
 * It sets the global variable to 1 when a signal is received.
 * @param signum The signal received (SIGUSR1 or SIGUSR2).
 */

volatile int	g_signal_received = 0;

void	ft_response(int signum)
{
	g_signal_received = 1;
	(void)signum;
}

/**
 * Sends a signal to the specified process based on the bit value.
 * This function sends either SIGUSR1 or SIGUSR2 to
 * the process with the given PID.
 * SIGUSR1 is sent if the bit is 1, and SIGUSR2 if the bit is 0.
 * If the signal cannot be sent, an error message is printed
 * and the program exits.
 *
 * @param pid The process ID of the recipient.
 * @param bit The bit to be sent (1 for SIGUSR1, 0 for SIGUSR2).
 */

void	send_bit(int pid, int bit)
{
	int	signal_to_send;

	if (bit == 1)
		signal_to_send = SIGUSR2;
	else
		signal_to_send = SIGUSR1;
	if (kill(pid, signal_to_send) == -1)
	{
		ft_putstr_fd("Error sending signal\n", 2);
		exit(EXIT_FAILURE);
	}
}

/**
 * Sends the bits of a character one by one to the specified process.

* The character is sent bit by bit starting
* from the most significant bit (MSB).
 * After each bit is sent, the function waits
 * for a small amount of time (800 microseconds)
 * to ensure proper signal processing.
 *It then waits for a response using the global variable `g_response`.
 *
 * @param pid The process ID of the recipient.
 * @param c The character to be sent.
 */

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_bit(pid, (c >> i) & 1);
		usleep(800);
		i--;
	}
	while (!g_signal_received)
		pause ();
	g_signal_received = 0;
}

/**
 * Sends a string to the specified process ID.
 * Each character in the string is sent bit by bit using `send_char`,
 * and a null character (`'\0'`) is sent at the end to mark the
 * termination of the string.
 *
 * @param pid The process ID of the recipient.
 * @param str The string to be sent.
 *            If `str` is NULL, the function does nothing.
 */

void	send_str(int pid, char *str)
{
	if (!str)
		return ;
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}

/**
 * Main function for the client program.
 * The program sends a string to a server using UNIX signals.
 *
 * It takes two arguments:
 * 1. The server's PID (process ID).
 * 2. The string to be sent to the server.
 *
 * Validates the PID and sets up a signal handler to receive
 * confirmations from the server.
 *
 * Usage:
 * ./client <pid> <string>
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return Always returns 0 on successful execution.
 */

int	main(const int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <pid> <string>\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR2, ft_response);
	send_str(pid, argv[2]);
	return (0);
}
