/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:30:59 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/09 10:08:03 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extracts variable name from $VAR format.
 * 
 * @param str The string after '$'.
 * @return A newly allocated substring of the variable name.
 */
char	*extract_var_name(const char *str)
{
	int		len;
	char	*name;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, len + 1);
	return (name);
}

/**
 * @brief Concatenates s1 + s2 and frees s1.
 * 
 * @param s1 The string to free.
 * @param s2 The second string.
 * @return The new combined string.
 */
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, len1 + 1);
	ft_strlcpy(joined + len1, s2, len2 + 1);
	free(s1);
	return (joined);
}

/**
 * @brief Appends a character to a string and frees the original string.
 * 
 * @param s The base string to extend.
 * @param c The character to append.
 * @return A new string with character added.
 */
char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}

/**
 * @brief Sorts a NULL-terminated array of strings alphabetically.
 * 
 * @param arr The array to sort.
 */
void	ft_sort_str_array(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i]) + 1) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
