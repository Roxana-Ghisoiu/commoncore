/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:00:00 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 19:23:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_utils.h"

void	clip_enemy_bounds(t_game *g, double ty, int sx, t_enemy_bounds *b)
{
	int	h;

	h = HEIGHT / 2 + g->look_offset + g->camera_height;
	b->sprite_height = (int)(HEIGHT / ty);
	if (b->sprite_height < 1)
		b->sprite_height = 1;
	b->sprite_width = b->sprite_height;
	b->real_start_x = sx - b->sprite_width / 2;
	b->draw_start_x = b->real_start_x;
	b->draw_end_x = sx + b->sprite_width / 2;
	b->draw_start_y = -b->sprite_height / 2 + h;
	b->draw_end_y = b->sprite_height / 2 + h;
	if (b->draw_start_y < 0)
		b->draw_start_y = 0;
	if (b->draw_end_y >= HEIGHT)
		b->draw_end_y = HEIGHT - 1;
	if (b->draw_start_x < 0)
		b->draw_start_x = 0;
	if (b->draw_end_x >= WIDTH)
		b->draw_end_x = WIDTH - 1;
}

static void	draw_enemy_if_visible(t_game *g, t_enemy *e,
	t_enemy_bounds *b, double ty)
{
	int	stripe;
	int	screen_x;

	screen_x = (int)((WIDTH / 2) * (1 + b->tx_camera / ty));
	clip_enemy_bounds(g, ty, screen_x, b);
	if (b->draw_end_x < 0 || b->draw_start_x >= WIDTH)
		return ;
	stripe = b->draw_start_x;
	while (stripe < b->draw_end_x)
	{
		if (ty > 0 && stripe >= 0 && stripe < WIDTH
			&& ty < g->z_buffer[stripe])
			draw_enemy_stripe(g, e, stripe, b);
		stripe++;
	}
}

int	render_one_enemy(t_game *g, t_enemy *e)
{
	t_enemy_bounds	b;
	double			tx;
	double			ty;

	ft_memset(&b, 0, sizeof(t_enemy_bounds));
	calculate_transform(g, e, &tx, &ty);
	if (ty <= 0.0)
		return (1);
	b.tx_camera = tx;
	draw_enemy_if_visible(g, e, &b, ty);
	return (0);
}

void	render_enemies(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->num_enemies)
	{
		render_one_enemy(g, &g->enemies[i]);
		i++;
	}
}

void	calculate_transform(t_game *g, t_enemy *e,
	double *transform_x, double *transform_y)
{
	double	dx;
	double	dy;
	double	inv_det;

	dx = e->x - g->player.x;
	dy = e->y - g->player.y;
	inv_det = 1.0 / (g->player.plane_x * g->player.dir_y
			- g->player.dir_x * g->player.plane_y);
	*transform_x = inv_det * (g->player.dir_y * dx - g->player.dir_x * dy);
	*transform_y = inv_det * (-g->player.plane_y * dx
			+ g->player.plane_x * dy);
}
