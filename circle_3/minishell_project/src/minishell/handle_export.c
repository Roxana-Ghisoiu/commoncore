/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:32:31 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 17:34:31 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:00:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 18:00:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_export_command(const char *input)
{
	while (*input == ' ')
		input++;
	return (ft_strncmp(input, "export", 6) == 0
		&& (input[6] == '\0' || input[6] == ' '));
}

void	process_export_directly(t_shell *sh, const char *input)
{
	char	**args;

	args = split_args_preserving_quotes(input);
	if (!args)
		return ;
	builtin_export(sh, args, STDOUT_FILENO);
	ft_free_split(args);
}
