/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:27:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 12:32:16 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Changes the current working directory.
 * 
 * @param sh The shell structure (contains envp).
 * @param args The arguments (args[1] = path).
 * @return int 0 on success, 1 on error.
 */
int	builtin_cd(t_shell *sh, char **args)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!args[1])
	{
		ft_putendl_fd("minishell: cd: missing argument", 2);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(args[1]) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (old_pwd)
		update_env_var(&sh->env_list, "OLDPWD", old_pwd);
	if (new_pwd)
		update_env_var(&sh->env_list, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
