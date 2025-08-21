/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:50:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/05/04 16:08:15 by rghisoiu         ###   ########.fr       */
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
 * @brief Create a new environment variable and add it to the list.
 *
 * @param env_list Pointer to the environment list.
 * @param key The name of the new variable.
 * @param value The value of the new variable.
 */
static t_env	*allocate_new_env_var(const char *key, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	new_var->key = ft_strdup(key);
	if (!new_var->key)
	{
		free(new_var);
		return (NULL);
	}
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->next = NULL;
	return (new_var);
}

static void	create_new_env_var(t_env **env_list,
	const char *key,
	const char *value)
{
	t_env	*new_var;
	t_env	*tail;

	new_var = allocate_new_env_var(key, value);
	if (!new_var)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_var;
		return ;
	}
	tail = *env_list;
	while (tail->next)
		tail = tail->next;
	tail->next = new_var;
}

/**
 * @brief Updates or adds an environment variable to the list.
 *
 * If the key exists, its value is updated. Otherwise, a new
 * environment variable is added.
 *
 * @param env_list Pointer to the environment list.
 * @param key The name of the variable.
 * @param value The value to assign to the variable.
 */
void	update_env_var(t_env **env_list, const char *key, const char *value)
{
	t_env	*env;

	if (!key)
		return ;
	env = *env_list;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env->value);
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = NULL;
			return ;
		}
		env = env->next;
	}
	create_new_env_var(env_list, key, value);
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
