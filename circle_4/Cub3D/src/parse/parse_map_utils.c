/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:45:00 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/21 11:31:21 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parse_map_utils.h"

int	get_max_line_length(char **map, int count, const char *new_line)
{
	int	max;
	int	len;
	int	i;

	if (new_line)
		max = strlen(new_line);
	else
		max = 0;
	i = 0;
	while (i < count)
	{
		len = strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	copy_old_lines(char **new_map, char **map, int count, int max_len)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_map[i] = malloc(max_len + 1);
		if (!new_map[i])
			exit_error("❌ malloc failed for map line");
		strcpy(new_map[i], map[i]);
		memset(new_map[i] + strlen(map[i]), ' ',
			max_len - strlen(map[i]));
		new_map[i][max_len] = '\0';
		free(map[i]);
		i++;
	}
}

void	add_last_line(char **new_map, int count, char *line, int max_len)
{
	new_map[count] = malloc(max_len + 1);
	if (!new_map[count])
		exit_error("❌ malloc failed for last line");
	strcpy(new_map[count], line);
	memset(new_map[count] + strlen(line), ' ',
		max_len - strlen(line));
	new_map[count][max_len] = '\0';
	new_map[count + 1] = NULL;
}

void	set_dir_n_s(t_game *game, char dir, double fov)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = fov;
		game->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -fov;
		game->player.plane_y = 0;
	}
}

void	set_dir_e_w(t_game *game, char dir, double fov)
{
	if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = fov;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -fov;
	}
}
