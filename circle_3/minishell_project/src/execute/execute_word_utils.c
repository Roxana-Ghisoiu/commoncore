/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:53:56 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 14:40:20 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes execve with environment and exits if it fails.
 * 
 * This function is only called inside the child process.
 */
static void	child_execve_block(t_shell *sh, char *path, char **args)
{
	char	**envp;

	envp = convert_env_to_array(sh->env_list);
	execve(path, args, envp);
	perror("minishell");
	free_str_array(envp);
	exit(EXIT_FAILURE);
}

/**
 * @brief Forks and executes a command using execve.
 * 
 * Updates sh->exit_code with the result of the command.
 */
int	fork_and_execute(t_shell *sh, char *path, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		child_execve_block(sh, path, args);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_code = WEXITSTATUS(status);
	else
		sh->exit_code = 1;
	return (sh->exit_code);
}

/**
 * @brief Returns the number of environment variables.
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
 * @brief Converts the env linked list to a NULL-terminated char** array.
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
 * @brief Executes a command with redirections, if any.
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
