/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:12:17 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/04 18:33:49 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup (char *src)
{
	int	i = 0;
	char	*dest;

	while (src[i])
		i++;
	dest = malloc (sizeof (char) * (i + 1));
	if (!dest)
		return (NULL);

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	buffer_read;
	static int	buffer_pos;
	int		i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	while(1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read (fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break;
		}
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos -1] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int	main (void)
{
	char	*a;
	int	fd;

	fd = open ("test2.txt", O_RDONLY);
	a = get_next_line (fd);
	printf ("%s", a);
	close (fd);
	free(a);
	return (0);
}
