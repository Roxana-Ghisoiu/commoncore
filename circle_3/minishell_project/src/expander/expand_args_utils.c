/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:17:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 12:34:31 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns the number of elements in a NULL-terminated string array.
 */
int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}
/*
 * @brief Expands a single argument if it is a bare unquoted asterisk.
 */
/*static char	**expand_single_arg(char **expanded, const char *arg, int index)
{
	char	**globs;
	int		j;

	if (index > 0 && ft_strncmp(arg, "*", 2) == 0 && !is_quoted(arg))
	{
		globs = expand_asterisk();
		j = 0;
		while (globs && globs[j])
		{
			expanded = add_entry_to_array
				(expanded, ft_arrlen(expanded), globs[j]);
			j++;
		}
		ft_free_split(globs);
	}
	else
		expanded = add_entry_to_array(expanded, ft_arrlen(expanded), arg);
	return (expanded);
}
*/

/**
 * @brief Expands the list of tokens by applying globbing (*), but only if
 *        the token was not quoted.
 *
 * @param tokens The list of tokens parsed from input.
 * @return A new NULL-terminated string array with globbing applied.
 */
char	**expand_args_globbing_from_tokens(t_token *tokens)
{
	char	**new_args;
	int		i;

	new_args = ft_calloc(1024, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (!tokens->was_quoted && has_unquoted_asterisk(tokens->content))
			new_args[i] = replace_asterisk_with_files(tokens->content);
		else
			new_args[i] = ft_strdup(tokens->content);
		tokens = tokens->next;
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}

/**
 * @brief Applies globbing to the token list.
 *
 * If a token contains an unquoted asterisk, it replaces it with matching files.
 * Only affects unquoted tokens, does not touch quoted ones.
 *
 * @param tokens Address to token list, updated in-place.
 */
void	expand_args_globbing(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		if (!curr->was_quoted && has_unquoted_asterisk(curr->content))
		{
			free(curr->content);
			curr->content = replace_asterisk_with_files("*");
		}
		curr = curr->next;
	}
}
