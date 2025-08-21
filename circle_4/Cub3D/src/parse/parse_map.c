/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:28:49 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 16:14:37 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parse_map_utils.h"

char	**append_map_line(char **map, char *line)
{
	int		count;
	char	**new_map;
	int		max_len;

	count = 0;
	if (map)
		while (map[count])
			count++;
	max_len = get_max_line_length(map, count, line);
	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		exit_error("❌ malloc failed in append_map_line");
	copy_old_lines(new_map, map, count, max_len);
	add_last_line(new_map, count, line, max_len);
	free(map);
	return (new_map);
}

void	finalize_map_dimensions(t_config *config)
{
	int	i;
	int	len;
	int	max_len;

	i = 0;
	max_len = 0;
	while (config->map[i])
	{
		len = strlen(config->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	config->map_height = i;
	config->map_width = max_len;
}

static int	spawn_if_player(char **map, int x, int y, t_game *game)
{
	if (strchr("NSEW", map[y][x]))
	{
		game->player.x = x + 0.5;
		game->player.y = y + 0.5;
		game->player.dir = map[y][x];
		map[y][x] = '0';
		set_player_direction(game, game->player.dir);
		printf("🧍 Player direction set: dir_x = %.1f, dir_y = %.1f\n",
			game->player.dir_x, game->player.dir_y);
		printf("📷 Camera plane set: plane_x = %.2f, plane_y = %.2f\n",
			game->player.plane_x, game->player.plane_y);
		return (1);
	}
	return (0);
}

void	handle_enemy_tile(t_game *game, char **map, int x, int y)
{
	game->enemies[game->num_enemies].x = x + 0.5;
	game->enemies[game->num_enemies].y = y + 0.5;
	game->enemies[game->num_enemies].can_move = false;
	printf("✅ Enemy detected at map (%d, %d)\n", x, y);
	printf("→ world (%.1f, %.1f)\n",
		game->enemies[game->num_enemies].x,
		game->enemies[game->num_enemies].y);
	game->num_enemies++;
	map[y][x] = '0';
}

void	find_player_spawn(t_game *game)
{
	int		x;
	int		y;
	int		found;
	char	**map;

	found = 0;
	y = 0;
	map = game->config.map;
	if (!map)
		exit_error("Map not initialized");
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!found && spawn_if_player(map, x, y, game))
				found = 1;
			if (map[y][x] == 'M')
				handle_enemy_tile(game, map, x, y);
			x++;
		}
		y++;
	}
	if (!found)
		exit_error("Player start position not found");
}
