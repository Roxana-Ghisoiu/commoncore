/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:30:59 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/01 17:08:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extracts the name of the variable after $.
 * 
 * @param str The string starting just after the '$' character.
 * @return A newly allocated variable name string.
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
 * @brief Concatenates two strings and frees the first one.
 * 
 * @param s1 The first string (will be freed).
 * @param s2 The second string.
 * @return A newly allocated string containing s1 + s2.
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
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	ft_strlcpy(joined + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	free(s1);
	return (joined);
}

/**
 * @brief Appends a single character to the end of a string.
 * 
 * @param s The string to append to (will be freed).
 * @param c The character to append.
 * @return A newly allocated string with c appended to s.
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
