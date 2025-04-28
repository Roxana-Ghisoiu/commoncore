/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_for_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:45:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 17:45:27 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes a normal (non-export) input line.
 */
void	process_non_export(t_shell *sh, const char *input)
{
	char		*expanded;
	t_token		*tokens;

	expanded = expand_line(sh, input);
	if (!expanded)
		return ;
	tokens = tokenize_input(expanded);
	if (!tokens)
	{
		free(expanded);
		return ;
	}
	expand_args_globbing(&tokens);
	sh->tokens = tokens;
	sh->root = build_parse_tree(&sh->tokens);
	free(expanded);
	execute_parsed_tree(sh);
	free_tree(sh->root);
	sh->root = NULL;
}
