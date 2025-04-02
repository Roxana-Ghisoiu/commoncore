/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:08:07 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/01 12:13:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a directory entry to the result array.
 * 
 * @param result The current array of filenames.
 * @param count The current count of filenames.
 * @param name The name of the new file to add.
 * @return A new array with the added entry, or NULL on failure.
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
			result = add_entry_to_array(result, count++, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	ft_sort_str_array(result);
	return (result);
}
