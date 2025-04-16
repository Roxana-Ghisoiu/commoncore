/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:53:56 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 20:49:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute a command by forking and using execve.
 *
 * @param sh The shell data.
 * @param path Full path to the executable.
 * @param args Arguments to the command (null-terminated).
 * @return The exit status of the command.
 */
int	fork_and_execute(t_shell *sh, char *path, char **args)
{
	pid_t	pid;
	int		status;
	char	**envp;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
	{
		envp = convert_env_to_array(sh->env_list);
		execve(path, args, envp);
		perror("minishell");
		free_str_array(envp);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * @brief Count the number of elements in the environment list.
 *
 * @param env The linked list of environment variables.
 * @return The number of variables.
 */
static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/**
 * @brief Convert linked list of environment variables into a char** array.
 *        Each entry is in the form "KEY=VALUE".
 *
 * @param env The linked list of environment variables.
 * @return Newly allocated array of strings for execve(), NULL-terminated.
 */
char	**convert_env_to_array(t_env *env)
{
	char	**envp;
	char	*entry;
	int		i;
	int		size;

	size = env_list_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		entry = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(entry, env->value);
		free(entry);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * @brief Executes a command node, handling redirections.
 * 
 * Saves STDIN/STDOUT, prepares redirections,
 * executes command, then restores fds.
 * 
 * @param sh Shell data
 * @param path Path to the executable
 * @param args Arguments to the command
 * @param node Command node (for redirection info)
 * @return Exit status
 */
int	execute_with_redir(t_shell *sh, char *path, char **args, t_node *node)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_in == -1 || saved_out == -1)
	{
		perror("minishell: dup");
		return (1);
	}
	if (prepare_redirections(node))
	{
		close(saved_in);
		close(saved_out);
		return (1);
	}
	status = fork_and_execute(sh, path, args);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (status);
}
