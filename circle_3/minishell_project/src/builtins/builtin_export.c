/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:45:14 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/05/04 16:07:02 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints an error message for an invalid export identifier.
 * 
 * @param arg The invalid argument.
 */
static void	print_export_error(const char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/**
 * @brief Processes a single export argument (KEY=VALUE).
 * 
 * @param sh The shell structure.
 * @param arg The export argument to process.
 */
static void	process_export_var(t_shell *sh, char *arg)
{
	char	*equal;
	char	*clean_value;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return ;
	*equal = '\0';
	if (is_valid_varname(arg))
	{
		clean_value = remove_surrounding_quotes(equal + 1);
		if (clean_value)
		{
			update_env_var(&sh->env_list, arg, clean_value);
			free(clean_value);
		}
	}
	else
		print_export_error(arg);
	*equal = '=';
}

/**
 * @brief Adds or updates environment variables.
 * 
 * @param sh The shell structure.
 * @param args The arguments (KEY=VALUE format).
 * @param fd_out The output file descriptor.
 * @return int Always returns 0.
 */
int	builtin_export(t_shell *sh, char **args, int fd_out)
{
	int	i;

	if (!args[1])
		return (builtin_env(sh, NULL, fd_out));
	i = 1;
	while (args[i])
	{
		process_export_var(sh, args[i]);
		i++;
	}
	return (0);
}
