/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:30:00 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/21 13:36:39 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include <string.h>
#include <math.h>

#define TILE_SIZE      10
#define COLOR_WALL     0x888888
#define COLOR_FLOOR    0xCCCCCC
#define COLOR_PLAYER   0xFF0000
#define COLOR_DIR      0x00FF00

void	draw_tile(t_game *g, int draw_x, int draw_y, int color)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			px = draw_x + x;
			py = draw_y + y;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				((int *)g->frame.addr)[py * WIDTH + px] = color;
			x++;
		}
		y++;
	}
}

void	draw_player_square(t_game *g, int cx, int cy)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			px = cx + x - TILE_SIZE / 2;
			py = cy + y - TILE_SIZE / 2;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				((int *)g->frame.addr)[py * WIDTH + px] = COLOR_PLAYER;
			x++;
		}
		y++;
	}
}

void	draw_player_direction(t_game *g, int cx, int cy)
{
	int	i;
	int	x;
	int	y;

	i = 1;
	while (i < 6)
	{
		x = cx + g->player.dir_x * i;
		y = cy + g->player.dir_y * i;
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			((int *)g->frame.addr)[y * WIDTH + x] = COLOR_DIR;
		i++;
	}
}
