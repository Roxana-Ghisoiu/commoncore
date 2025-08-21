/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy_logic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:06:59 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 02:09:18 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "string_utils.h"

void	update_enemy_position(t_game *g, t_enemy *e)
{
	t_vec2	dir;
	double	dist;
	double	step_x;
	double	step_y;

	dir = get_direction_to_player(g, e->x, e->y);
	dist = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (dist < 0.5)
		return ;
	step_x = dir.x / dist * 0.03;
	step_y = dir.y / dist * 0.03;
	if (is_walkable(g, e->x + step_x, e->y))
		e->x += step_x;
	if (is_walkable(g, e->x, e->y + step_y))
		e->y += step_y;
}

void	update_enemies(t_game *g)
{
	int		i;
	t_enemy	*e;

	i = 0;
	while (i < g->num_enemies)
	{
		e = &g->enemies[i];
		if (e->can_move && has_line_of_sight(g, e->x, e->y))
			update_enemy_position(g, e);
		i++;
	}
}

static void	prepare_stripe_drawing(t_stripe_context *ctx)
{
	ctx->step = 1.0 * ctx->e->texture.height / ctx->b->sprite_height;
	ctx->tex_pos = (ctx->b->draw_start_y - (HEIGHT / 2
				+ ctx->g->look_offset + ctx->g->camera_height)
			+ ctx->b->sprite_height / 2) * ctx->step;
}

static void	draw_enemy_stripe_loop(t_stripe_context *ctx)
{
	int	y;
	int	tex_y;
	int	color;

	y = ctx->b->draw_start_y;
	while (y < ctx->b->draw_end_y)
	{
		tex_y = (int)ctx->tex_pos & (ctx->e->texture.height - 1);
		ctx->tex_pos += ctx->step;
		color = ctx->e->texture.data[ctx->e->texture.width
			* tex_y + (int)ctx->b->tx];
		if ((color & 0x00FFFFFF) != 0)
			set_pixel(&ctx->g->frame, ctx->stripe, y, color);
		y++;
	}
}

void	draw_enemy_stripe(t_game *g, t_enemy *e,
	int stripe, t_enemy_bounds *b)
{
	t_stripe_context	ctx;

	ft_bzero(&ctx, sizeof(t_stripe_context));
	ctx.g = g;
	ctx.e = e;
	ctx.b = b;
	ctx.stripe = stripe;
	prepare_stripe_drawing(&ctx);
	ctx.b->tx = (int)((ctx.stripe - ctx.b->real_start_x)
			* (double)ctx.e->texture.width / ctx.b->sprite_width);
	draw_enemy_stripe_loop(&ctx);
}
