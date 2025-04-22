/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:52:35 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/17 15:05:56 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a pipe and handles any error.
 *
 * This function wraps the pipe system call and exits on failure,
 * ensuring the program doesn't continue in an invalid state.
 *
 * @param pipe_fd Array of two integers where the file descriptors
 *  will be stored.
 */
void	create_pipe_or_exit(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Closes both ends of a pipe safely.
 *
 * This is used after the parent no longer needs the pipe file descriptors.
 *
 * @param pipe_fd Array containing the read and write ends of the pipe.
 */
void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
