/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:50:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 13:50:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Search for the value of an environment variable in the list.
 *
 * @param env The linked list of environment variables.
 * @param key The name of the variable to find.
 * @return A newly allocated string with the value, or NULL if not found.
 */
char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Updates or adds an environment variable to the list.
 *
 * If the key already exists, its value is updated. Otherwise, a new
 * environment variable is added to the front of the list.
 *
 * @param env_list Pointer to the environment list.
 * @param key The name of the variable.
 * @param value The value to assign to the variable.
 */
void	update_env_var(t_env **env_list, const char *key, const char *value)
{
	t_env	*env;

	if (!key || !value)
		return ;
	env = *env_list;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = *env_list;
	*env_list = env;
}

/**
 * @brief Removes an environment variable from the list by key.
 *
 * @param env_list Pointer to the environment list.
 * @param key The name of the variable to remove.
 */
void	remove_env_var(t_env **env_list, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!env_list || !*env_list || !key)
		return ;
	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
