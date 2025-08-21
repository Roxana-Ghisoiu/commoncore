/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:02:33 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 01:35:32 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"
#include "raycast_utils.h"
#include <math.h>

static void	fill_texinfo(t_texinfo *info, t_game *g,
	t_ray *r, int side)
{
	info->game = g;
	info->ray = r;
	info->side = side;
}

static double	calc_perp_wall_dist(t_game *g, t_ray *r, int side)
{
	if (side == 0)
		return ((r->map_x - g->player.x + (1 - r->step_x) / 2) / r->dir_x);
	else
		return ((r->map_y - g->player.y + (1 - r->step_y) / 2) / r->dir_y);
}

static void	cast_ray(t_game *g, int x)
{
	t_ray		r;
	t_texinfo	info;
	char		tile;
	int			side;

	ft_memset(&r, 0, sizeof(t_ray));
	ft_memset(&info, 0, sizeof(t_texinfo));
	init_ray_data(&r, g, 2 * x / (double)WIDTH - 1);
	set_steps(&r, g);
	perform_dda(g, &r, &tile, &side);
	fill_texinfo(&info, g, &r, side);
	draw_texture_column(g, x, &info);
	g->z_buffer[x] = calc_perp_wall_dist(g, &r, side);
}

void	render_walls(t_game *g)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(g, x);
		x++;
	}
}
