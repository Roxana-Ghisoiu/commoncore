/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:10:54 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 16:15:06 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	read_and_parse_lines(t_game *game, int fd)
{
	char	*line;
	size_t	len;

	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		parse_texture_line(line, game);
		free(line);
	}
}

void	set_player_direction(t_game *game, char dir)
{
	double	fov;

	fov = 0.66;
	set_dir_n_s(game, dir, fov);
	set_dir_e_w(game, dir, fov);
}
