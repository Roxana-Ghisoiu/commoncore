/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:08:07 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/09 10:07:39 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a new filename to a dynamic array of filenames.
 * 
 * @param result Current array.
 * @param count Current number of entries.
 * @param name The new filename to add.
 * @return A new array with the name added.
 */
char	**add_entry_to_array(char **result, int count, const char *name)
{
	char	**temp;

	temp = ft_calloc(count + 2, sizeof(char *));
	if (!temp)
		return (NULL);
	ft_memcpy(temp, result, count * sizeof(char *));
	temp[count] = ft_strdup(name);
	free(result);
	return (temp);
}

/**
 * @brief Expands '*' into a list of non-hidden filenames in current dir.
 * 
 * @return A NULL-terminated array of matching filenames.
 */
char	**expand_asterisk(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**result;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	result = ft_calloc(1, sizeof(char *));
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			result = add_entry_to_array(result, count, entry->d_name);
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	ft_sort_str_array(result);
	return (result);
}
