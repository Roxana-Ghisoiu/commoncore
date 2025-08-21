/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:28:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/20 15:28:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Calculates the length of a string.
 * This function returns the length of the string `s`,
 * excluding the null-terminator.
 * @param s The string whose length is to be calculated.
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
 * Joins two strings into a new string.
 * This function concatenates `s1` and `s2`
 * into a new string and returns it.
 * The newly allocated string contains the content 
 * of `s1` followed by the content of `s2`.
 * @param s1 The first string to be joined.
 * @param s2 The second string to be joined.
 * @return char* The concatenated string or NULL if memory allocation fails.
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
	free((void *)(s1));
	return (tab);
}

/**
 * Finds the first occurrence of a character in a string.
 * This function searches for the first occurrence 
 * of the character `c` in the string `s`.
 * If the character is found, it returns a pointer 
 * to the first occurrence,otherwise returns NULL.
  * @param s The string to be searched.
 * @param c The character to search for.
 * @return char* A pointer to the first occurrence 
 * of `c` or NULL if not found.
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
 * Extracts a substring from a string.
 * This function returns a new string containing
 * a substring of `s`, starting at position
 * `start` and having a maximum length of `len`. 
 * If the `start` is out of range, an empty string is returned.
 * @param s The string from which to extract the substring.
 * @param start The starting position of the substring.
 * @param len The maximum length of the substring.
 * @return char* The extracted substring or NULL if memory allocation fails.
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
 * Duplicates a string.
 * This function returns a new string 
 *that is a duplicate of the string `s1`,including the null-terminator.
 * @param s1 The string to be duplicated.
 * @return char* The duplicated string or NULL if memory allocation fails.
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
