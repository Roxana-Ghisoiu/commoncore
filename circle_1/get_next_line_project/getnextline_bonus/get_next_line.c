/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:20:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/11/20 15:21:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
* Reads a line from a file descriptor.
* The `get_next_line` function returns 
* a line read from the file associated with 
*the given file descriptor `fd`,including the newline 
* character `\n`. If the end of file
* is reached or an error occurs, it returns NULL.
* @param fd The file descriptor to read from.
* @return char* A line read from the file or NULL
* if an error occurs or EOF is reached.
 */
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	line = NULL;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	stash = stash_filling(fd, stash, buffer);
	if (*stash == 0)
	{
		free(stash);
		return (stash = 0);
	}
	line = extract_line(stash, line);
	stash = extract_new_stash(stash);
	return (line);
}

/**
 * Fills the stash with data read from the file.
 * This function reads data from the file using `read` 
 * and adds the read data to `stash`.
* It stops when a newline character `\n` 
* is found or no more data is available to read.
 * @param fd The file descriptor to read from.
 * @param stash The previous stash, containing already read data.
 * @param buffer The buffer to store data read from the file.
 * @return char* The updated stash with the read data.
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
			free(buffer);
			return (NULL);
		}
		buffer[nbytes] = 0;
		stash = ft_strjoin(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

/**
 * Extracts the updated stash, excluding the current line.
 * This function extracts only the remaining part of 
 * the stash after the current line,
 * keeping only the content following the newline character `\n`.
 * @param stash The stash containing the entire read content.
 * @return char* The updated stash excluding the current line.
 */
char	*extract_new_stash(char *stash)
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
	free(stash);
	new_stash[i] = 0;
	return (new_stash);
}

/**
 * Extracts the current line from the stash.
 * This function extracts the current line from the stash,
* up to the newline character `\n`,
 * and returns it as a new string.
 * @param stash The stash containing the read data.
 * @param line The extracted line.
 * @return char* The extracted line from the stash.
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

/* int main()
{
	int	fd;

	fd = open("text.txt", O_RDONLY);
	printf("GNL 1: %s", get_next_line(fd));
	printf("GNL 2: %s", get_next_line(fd));
	printf("GNL 3: %s", get_next_line(fd));
	printf("GNL 4: %s", get_next_line(fd));
	printf("GNL 5: %s", get_next_line(fd));
	printf("GNL 6: %s", get_next_line(fd));
	printf("GNL 7: %s", get_next_line(fd));
	printf("GNL 8: %s", get_next_line(fd));
	printf("GNL 9: %s", get_next_line(fd));
	close(fd);
} */
