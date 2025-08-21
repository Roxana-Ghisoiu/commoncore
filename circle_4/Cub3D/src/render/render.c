/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:48:53 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 14:26:07 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "draw_utils.h"
#include "doors.h"
#include <mlx.h>
#include <math.h>

static void	render_game_over(t_game *game)
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
	if (game->config.game_over.img)
	{
		x = (WIDTH - game->config.game_over.width) / 2;
		y = (HEIGHT - game->config.game_over.height) / 2;
		mlx_put_image_to_window(game->mlx, game->win,
			game->config.game_over.img, x, y);
	}
	else
	{
		mlx_string_put(game->mlx, game->win,
			WIDTH / 2 - 50, HEIGHT / 2, 0xFF0000, "GAME OVER");
	}
}

static void	render_ui(t_game *game)
{
	if (game->minimap_enabled)
		draw_minimap(game);
	draw_weapon(game);
	draw_crosshair(game);
	draw_health_bar(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

static void	render_alive_frame(t_game *game)
{
	update_enemies(game);
	render_background(game, (int *)game->frame.addr);
	render_walls(game);
	render_enemies(game);
	render_ui(game);
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_movement(game);
	check_auto_close_doors(game);
	if (game->health <= 0 && game->lives > 0)
	{
		game->lives--;
		game->health = 100;
	}
	if (game->lives == 0)
		render_game_over(game);
	else
		render_alive_frame(game);
	game->frame_count++;
	return (0);
}
