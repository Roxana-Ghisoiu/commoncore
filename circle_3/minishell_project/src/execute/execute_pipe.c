/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:39:57 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/22 18:58:32 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Redirects pipe file descriptors and executes the command.
 *
 * Called inside the child process after fork, this sets up the
 * redirection based on whether it's the left or right side of the pipe,
 * and then executes the command subtree.
 *
 * @param pipe_data Pipe context data for redirection and execution.
 */
static void	execute_child_process(t_pipe_data *pipe_data)
{
	if (pipe_data->end == 0)
	{
		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_data->pipe_fd);
	}
	else
	{
		dup2(pipe_data->pipe_fd[0], STDIN_FILENO);
		close_pipe(pipe_data->pipe_fd);
	}
	if (evaluate_execution(pipe_data->sh, pipe_data->tree) == -1)
		exit(pipe_data->sh->exit_code);
	exit(pipe_data->sh->exit_code);
}

/**
 * @brief Creates a child process and delegates execution.
 *
 * Forks a new process. If inside the child, it sets up pipe
 * redirection and executes the appropriate command.
 *
 * @param pipe_data Context containing execution and pipe info.
 * @return The PID of the created child process, or -1 on error.
 */
static pid_t	create_pipe_child(t_pipe_data *pipe_data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		execute_child_process(pipe_data);
	return (pid);
}

/**
 * @brief Forks two child processes for left and right nodes of the pipe.
 *
 * Each child receives the appropriate redirection and subtree to execute.
 *
 * @param sh Main shell structure.
 * @param node Pipe node containing left and right subcommands.
 * @param pipe_fd Pipe file descriptors.
 * @param pid Array to store child PIDs.
 */
static void	exec_pipe_fork(t_shell *sh, t_node *node, int *pipe_fd, pid_t *pid)
{
	t_pipe_data	pdata;

	pdata.pipe_fd = pipe_fd;
	pdata.sh = sh;
	pdata.end = 0;
	pdata.std_fd = STDOUT_FILENO;
	pdata.tree = node->left;
	pid[0] = create_pipe_child(&pdata);
	pdata.end = 1;
	pdata.std_fd = STDIN_FILENO;
	pdata.tree = node->right;
	pid[1] = create_pipe_child(&pdata);
}

/**
 * @brief Waits for both child processes and closes the pipe file descriptors.
 *
 * Also updates the shell exit code based on the result of the last command.
 *
 * @param sh Main shell structure.
 * @param pipe_fd Array containing read and write file descriptors.
 * @param pid Array of child PIDs to wait for.
 */
static void	wait_and_close_pipes(t_shell *sh, int *pipe_fd, pid_t *pid)
{
	int	status;

	close_pipe(pipe_fd);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		sh->exit_code = WEXITSTATUS(status);
	else
		sh->exit_code = 1;
}

/**
 * @brief Executes a pipeline between two commands.
 *
 * Handles creation of the pipe, forks both child processes,
 * redirects input/output accordingly, and waits for their completion.
 *
 * @param sh Main shell structure.
 * @param node Node of type TOK_PIPE representing the pipe operation.
 * @return Exit status of the last command in the pipeline.
 */
int	execute_pipe_node(t_shell *sh, t_node *node)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	create_pipe_or_exit(pipe_fd);
	exec_pipe_fork(sh, node, pipe_fd, pid);
	wait_and_close_pipes(sh, pipe_fd, pid);
	return (sh->exit_code);
}
