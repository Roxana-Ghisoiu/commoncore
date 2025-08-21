/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:22:39 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 02:25:58 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_utils.h"

#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10

void	draw_minimap_tile(t_game *g, int sx, int sy, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_SCALE)
	{
		x = 0;
		while (x < MINIMAP_SCALE)
		{
			set_pixel(&g->frame, sx + x, sy + y, color);
			x++;
		}
		y++;
	}
}

static int	get_tile_color(char c)
{
	if (c == '1')
		return (0xAAAAAA);
	if (c == 'D')
		return (0xAA5500);
	return (0x000000);
}

static void	draw_map_region(t_game *g, int px, int py)
{
	int	map_y;
	int	map_x;
	int	sx;
	int	sy;
	int	color;

	map_y = -MINIMAP_RADIUS;
	while (map_y <= MINIMAP_RADIUS)
	{
		map_x = -MINIMAP_RADIUS;
		while (map_x <= MINIMAP_RADIUS)
		{
			sx = (map_x + MINIMAP_RADIUS) * MINIMAP_SCALE + MINIMAP_OFFSET_X;
			sy = (map_y + MINIMAP_RADIUS) * MINIMAP_SCALE + MINIMAP_OFFSET_Y;
			if (py + map_y >= 0 && py + map_y < g->config.map_height
				&& px + map_x >= 0 && px + map_x < g->config.map_width)
			{
				color = get_tile_color(g->config.map[py + map_y][px + map_x]);
				draw_minimap_tile(g, sx, sy, color);
			}
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap(t_game *g)
{
	int	px;
	int	py;
	int	player_sx;
	int	player_sy;

	px = (int)g->player.x;
	py = (int)g->player.y;
	draw_map_region(g, px, py);
	player_sx = MINIMAP_OFFSET_X + MINIMAP_RADIUS * MINIMAP_SCALE;
	player_sy = MINIMAP_OFFSET_Y + MINIMAP_RADIUS * MINIMAP_SCALE;
	draw_minimap_tile(g, player_sx, player_sy, 0x00FF00);
}
