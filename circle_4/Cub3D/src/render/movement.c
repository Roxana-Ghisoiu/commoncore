/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:34:09 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 01:54:39 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	rotate_player(t_game *g, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * cos(rot)
		- g->player.dir_y * sin(rot);
	g->player.dir_y = old_dir_x * sin(rot)
		+ g->player.dir_y * cos(rot);
	g->player.plane_x = g->player.plane_x * cos(rot)
		- g->player.plane_y * sin(rot);
	g->player.plane_y = old_plane_x * sin(rot)
		+ g->player.plane_y * cos(rot);
}

void	strafe_player(t_game *g)
{
	double	px;
	double	py;
	double	len;
	int		dir;

	px = -g->player.dir_y;
	py = g->player.dir_x;
	len = sqrt(px * px + py * py);
	if (g->keys.d)
		dir = 1;
	else
		dir = -1;
	if (len != 0)
	{
		px /= len;
		py /= len;
	}
	if (g->config.map[(int)(g->player.y)]
		[(int)(g->player.x + dir * px * MOVE_SPEED)] != '1')
		g->player.x += dir * px * MOVE_SPEED;
	if (g->config.map[(int)(g->player.y + dir * py * MOVE_SPEED)]
		[(int)(g->player.x)] != '1')
		g->player.y += dir * py * MOVE_SPEED;
}

void	move_forward_backward(t_game *g)
{
	if (!g || !g->config.map)
		return ;
	if (g->keys.w)
	{
		if (is_walkable_tile(g->config.map[(int)(g->player.y)]
			[(int)(g->player.x + g->player.dir_x * MOVE_SPEED)]))
			g->player.x += g->player.dir_x * MOVE_SPEED;
		if (is_walkable_tile(g->config.map[(int)(g->player.y
					+ g->player.dir_y * MOVE_SPEED)][(int)(g->player.x)]))
			g->player.y += g->player.dir_y * MOVE_SPEED;
	}
	if (g->keys.s)
	{
		if (is_walkable_tile(g->config.map[(int)(g->player.y)]
			[(int)(g->player.x - g->player.dir_x * MOVE_SPEED)]))
			g->player.x -= g->player.dir_x * MOVE_SPEED;
		if (is_walkable_tile(g->config.map[(int)(g->player.y
					- g->player.dir_y * MOVE_SPEED)][(int)(g->player.x)]))
			g->player.y -= g->player.dir_y * MOVE_SPEED;
	}
	if (g->is_jumping)
		handle_jump(g);
}

void	rotate_if_needed(t_game *g)
{
	double	rotation;

	if (g->keys.right)
		rotation = ROT_SPEED;
	else
		rotation = -ROT_SPEED;
	rotate_player(g, rotation);
}

int	handle_movement(t_game *g)
{
	move_forward_backward(g);
	if (g->keys.d || g->keys.a)
		strafe_player(g);
	if (g->keys.left || g->keys.right)
		rotate_if_needed(g);
	render_walls(g);
	return (0);
}
