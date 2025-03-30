/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:31:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:30 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Search for the full path of a command using the PATH variable.
 *
 * @param sh Pointer to the shell structure containing environment list.
 * @param cmd The command to search for (e.g., "ls").
 * @return Full path to the command if found, NULL otherwise.
 */
char	*find_command_path(t_shell *sh, char *cmd)
{
	char	**paths;
	char	*path_value;
	char	*candidate;
	int		i;

	if (!cmd || ft_strchr(cmd, '/') || access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_value = get_env_value(sh->env_list, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	free(path_value);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoin_three(paths[i], "/", cmd);
		if (candidate && access(candidate, X_OK) == 0)
			return (ft_free_split(paths), candidate);
		free(candidate);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}
