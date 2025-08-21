/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:08:34 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 14:20:19 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "doors.h"
#include <math.h>

static void	handle_key_toggle(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_M)
		game->minimap_enabled = !game->minimap_enabled;
}

static void	handle_health(int keycode, t_game *game)
{
	if (keycode == KEY_H)
	{
		if (game->health > 0)
			game->health -= 5;
		if (game->health <= 0 && game->lives > 0)
		{
			game->lives--;
			game->health = 100;
		}
	}
}

int	key_press(int keycode, t_game *game)
{
	handle_key_toggle(keycode, game);
	handle_health(keycode, game);
	if (keycode == KEY_E)
		interact_with_door(game);
	if (keycode == KEY_ESC)
		clean_exit(game, 0);
	if (keycode == KEY_SPACE && !game->is_jumping)
	{
		game->is_jumping = 1;
		game->jump_time = 0;
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *g)
{
	int	cx;
	int	cy;
	int	dx;
	int	dy;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	dx = x - cx;
	dy = y - cy;
	if (dx != 0)
		rotate_player(g, dx * 0.0005);
	g->look_offset -= dy;
	if (g->look_offset > HEIGHT / 4)
		g->look_offset = HEIGHT / 4;
	if (g->look_offset < -HEIGHT / 4)
		g->look_offset = -HEIGHT / 4;
	mlx_mouse_move(g->mlx, g->win, cx, cy);
	return (0);
}
