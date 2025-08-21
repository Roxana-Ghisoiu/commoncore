/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:41:43 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/20 15:41:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * Reads the next line from a file descriptor.
 * This function returns the next line read from 
 * the given file descriptor `fd`. 
 * It uses a static buffer to store data between calls.
 * 
 * @param fd The file descriptor to read from.
 * @return char* The next line or NULL if an error occurs.
 */
char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	char		*buffer;

	line = NULL;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		free(buffer);
		stash[fd] = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	stash[fd] = stash_filling(fd, stash[fd], buffer);
	if (*stash[fd] == 0)
	{
		free (stash[fd]);
		return (stash[fd] = 0);
	}
	line = extract_line(stash[fd], line);
	stash[fd] = extract_new_stash(stash[fd]);
	return (line);
}

/**Fills the static buffer with data from the file descriptor.
 * This function reads data from the file 
 * descriptor `fd` into the buffer until 
 * a newline is encountered or the end of the file is reached.
 * 
 * @param fd The file descriptor to read from.
 * @param stash The static buffer to hold the data.
 * @param buffer The temporary buffer used for reading.
 * @return char* The updated buffer with the read data.
 */
char	*stash_filling(int fd, char *stash, char *buffer)
{
	ssize_t	nbytes;

	nbytes = 1;
	if (!stash)
		stash = ft_strdup("");
	while (nbytes > 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[nbytes] = 0;
		stash = ft_strjoin (stash, buffer);
		if ((ft_strchr(buffer, '\n')))
			break ;
	}
	free (buffer);
	return (stash);
}

/**
 * Extracts the new stash (remaining data after the newline).
 * This function creates a new stash from the data 
 * after the first newline character and frees the old stash.
 * 
 * @param stash The current buffer to extract from.
 * @return char* The new stash containing the data after the newline.
 */
char	*extract_new_stash(char	*stash)
{
	int		len;
	int		i;
	char	*new_stash;

	len = 0;
	i = 0;
	if (stash == NULL)
		return (NULL);
	while (stash[len] != '\n' && stash[len])
		len++;
	if (stash[len] == '\n')
		len++;
	new_stash = malloc((ft_strlen(stash) - len + 1) * sizeof(char));
	if (!new_stash)
		return (NULL);
	while (stash[len + i])
	{
		new_stash[i] = stash[len + i];
		i++;
	}
	free (stash);
	new_stash[i] = 0;
	return (new_stash);
}

/**
 * Extracts the line (up to and including the newline).
 * This function extracts a line from the stash, 
 * including the newline character.
 * 
 * @param stash The buffer containing the data.
 * @param line The variable to hold the extracted line.
 * @return char* The extracted line.
 */
char	*extract_line(char *stash, char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (stash == NULL)
		return (NULL);
	while (stash[len] != '\n' && stash[len])
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = 0;
	return (line);
}
