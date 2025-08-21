/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:48:39 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/20 15:48:44 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief Calculates the length of a string.
 * @param s The string to measure.
 * @return size_t The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief Joins two strings into a new dynamically allocated string.
 * This function concatenates `s1` and `s2`, frees `s1`, and returns the result.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return char* The new concatenated string or NULL on allocation failure.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	tab = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = 0;
	free ((void *)(s1));
	return (tab);
}

/**
 * @brief Finds the first occurrence of a character in a string.
 * @param s The string to search.
 * @param c The character to find.
 * @return char* A pointer to the first occurrence 
 * of `c` in `s` or NULL if not found.
 */
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

/**
 * @brief Extracts a substring from a string.
 * The substring starts at `start` and has a maximum length of `len`.
 * @param s The original string.
 * @param start The starting index.
 * @param len The maximum length of the substring.
 * @return char* The extracted substring or NULL on allocation failure.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*tab;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (malloc(1));
	if (len >= ft_strlen(s + start))
		len = ft_strlen(s + start);
	tab = malloc(sizeof(char) * (len) + 1);
	if (!tab)
		return (NULL);
	while (len > 0)
	{
		tab[i++] = s[start++];
		len--;
	}
	tab[i] = '\0';
	return (tab);
}

/**
 * @brief Duplicates a string into a new dynamically allocated string.
 * @param s1 The string to duplicate.
 * @return char* The duplicated string or NULL on allocation failure.
 */
char	*ft_strdup(const char *s1)
{
	char	*tab;
	int		i;
	int		len;

	len = ft_strlen(s1);
	i = 0;
	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
