/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:53:56 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/28 13:52:05 by rghisoiu         ###   ########.fr       */
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
