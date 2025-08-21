/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_health.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:15:25 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 18:48:05 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_utils.h"
#include <mlx.h>

#define BAR_WIDTH 100
#define BAR_HEIGHT 10
#define BAR_Y 20
#define HEART_COLOR 0xFF0000
#define HEART_RADIUS 3
#define HEART_SPACING 10
#define HEART_Y 20

void	draw_game_over_screen(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			set_pixel(&game->frame, x, y, 0x000000);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
	mlx_string_put(game->mlx, game->win, WIDTH / 2 - 50, HEIGHT / 2,
		0xFF0000, "GAME OVER");
}

static void	draw_single_heart(t_game *g, int cx, int cy)
{
	int	dx;
	int	dy;

	dy = -HEART_RADIUS - 1;
	while (++dy <= HEART_RADIUS)
	{
		dx = -HEART_RADIUS - 1;
		while (++dx <= HEART_RADIUS)
		{
			if (dx * dx + dy * dy <= HEART_RADIUS * HEART_RADIUS)
				set_pixel(&g->frame, cx + dx, cy + dy, HEART_COLOR);
		}
	}
}

void	draw_hearts(t_game *g)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	y = HEART_Y;
	while (++i < g->lives)
	{
		x = WIDTH - 10 - i * (HEART_RADIUS * 2 + HEART_SPACING);
		draw_single_heart(g, x, y);
	}
}

void	draw_health_bar(t_game *g)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	width;

	if (g->lives <= 0)
	{
		draw_game_over_screen(g);
		return ;
	}
	x = (WIDTH - BAR_WIDTH) / 2;
	y = BAR_Y;
	width = (g->health * BAR_WIDTH) / 100;
	j = -1;
	while (++j < BAR_HEIGHT)
	{
		i = -1;
		while (++i < BAR_WIDTH)
			set_pixel(&g->frame, x + i, y + j, 0x333333);
		i = -1;
		while (++i < width)
			set_pixel(&g->frame, x + i, y + j, 0x00FF00);
	}
	draw_hearts(g);
}
