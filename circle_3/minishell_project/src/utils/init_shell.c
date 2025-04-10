/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:36:58 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/10 12:07:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates and initializes the shell structure.
 * 
 * @param sh Pointer to the shell structure pointer.
 * @param envp The environment variables.
 */
void	init_shell(t_shell **sh, char **envp)
{
	*sh = malloc(sizeof(t_shell));
	if (!*sh)
	{
		perror("minishell: malloc failed");
		exit(EXIT_FAILURE);
	}
	(*sh)->env_list = create_env_list(envp);
	(*sh)->tokens = NULL;
	(*sh)->root = NULL;
	(*sh)->line_input = NULL;
	(*sh)->exit_code = 0;
}

/**
 * @brief Creates a new environment node from a string "KEY=VALUE".
 * 
 * @param entry The "KEY=VALUE" string.
 * @return A new t_env node, or NULL if allocation fails or invalid format.
 */
static t_env	*create_env_node(const char *entry)
{
	t_env	*node;
	char	*equal_sign;

	equal_sign = ft_strchr(entry, '=');
	if (!equal_sign)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_substr(entry, 0, equal_sign - entry);
	node->value = ft_strdup(equal_sign + 1);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/**
 * @brief Converts the environment array to a linked list.
 * 
 * @param envp The environment array.
 * @return The head of the linked list.
 */
t_env	*create_env_list(char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new = create_env_node(envp[i]);
		if (new)
		{
			new->next = head;
			if (head)
				head->prev = new;
			head = new;
		}
		i++;
	}
	return (head);
}

/**
 * @brief Frees the entire linked list of environment variables.
 * 
 * @param env The head of the list.
 */
void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

/**
 * @brief Frees memory used by the shell structure.
 * 
 * @param sh The shell structure to free.
 */
void	free_shell(t_shell *sh)
{
	if (!sh)
		return ;
	free_env_list(sh->env_list);
	if (sh->tokens)
		free_tokens(sh->tokens);
	if (sh->line_input)
		free(sh->line_input);
	// TODO: free_tree(sh->root); // (în viitor)
	free(sh);
}

