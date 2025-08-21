/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:11:26 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/21 11:20:29 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char	*read_line(int fd)
{
	char	buf;
	char	*line;
	char	*new_line;
	size_t	len;

	line = NULL;
	len = 0;
	while (read(fd, &buf, 1) == 1)
	{
		new_line = malloc(len + 2);
		if (!new_line)
			return (NULL);
		if (line)
		{
			memcpy(new_line, line, len);
			free(line);
		}
		new_line[len++] = buf;
		new_line[len] = '\0';
		line = new_line;
		if (buf == '\n')
			break ;
	}
	return (line);
}

void	parse_texture_line(char *line, t_game *game)
{
	if (strncmp(line, "NO ", 3) == 0)
		game->config.north_texture = strdup(line + 3);
	else if (strncmp(line, "SO ", 3) == 0)
		game->config.south_texture = strdup(line + 3);
	else if (strncmp(line, "WE ", 3) == 0)
		game->config.west_texture = strdup(line + 3);
	else if (strncmp(line, "EA ", 3) == 0)
		game->config.east_texture = strdup(line + 3);
	else if (strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0)
		parse_color_or_texture(line, &game->config);
	else if (is_map_line(line))
		game->config.map = append_map_line(game->config.map, line);
	else
	{
		free(line);
		exit_error("Invalid line in .cub file");
	}
}

void	parse_config(t_game *game, char *filename)
{
	int	fd;

	game->config.map = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open .cub file");
	read_and_parse_lines(game, fd);
	close(fd);
	finalize_map_dimensions(&game->config);
	find_player_spawn(game);
}
