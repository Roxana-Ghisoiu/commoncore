/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:20:24 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 02:08:12 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"
#include "raycast_utils.h"
#include <math.h>

int	compute_tex_x(t_texinfo *ti, double dist)
{
	double	wall_x;
	int		tex_x;

	if (ti->side == 0)
		wall_x = ti->game->player.y + dist * ti->ray->dir_y;
	else
		wall_x = ti->game->player.x + dist * ti->ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * ti->tex->width);
	if ((ti->side == 0 && ti->ray->dir_x > 0)
		|| (ti->side == 1 && ti->ray->dir_y < 0))
		tex_x = ti->tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_column_pixels(t_game *g, int x, t_texinfo *ti, int tex_x)
{
	int		y;
	int		d;
	int		tex_y;
	int		*buffer;

	y = ti->info.start;
	buffer = (int *)g->frame.addr;
	while (y < ti->info.end)
	{
		d = y * 256 - (HEIGHT + 2 * (g->look_offset
					+ g->camera_height)) * 128 + ti->info.height * 128;
		tex_y = ((d * ti->tex->height) / ti->info.height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ti->tex->height)
			tex_y = ti->tex->height - 1;
		buffer[y * WIDTH + x] = ti->tex->data[
			ti->tex->width * tex_y + tex_x];
		y++;
	}
}

void	perform_dda(t_game *g, t_ray *r, char *tile, int *side)
{
	while (1)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			*side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			*side = 1;
		}
		if ((r->map_y < 0 || r->map_y >= g->config.map_height)
			|| (r->map_x < 0 || r->map_x >= g->config.map_width))
			exit_error("❌ Ray went out of map bounds");
		*tile = g->config.map[r->map_y][r->map_x];
		if (*tile == '1' || *tile == 'D')
			break ;
	}
}

static t_texture	*get_texture(t_game *g, t_ray *r, int side, char tile)
{
	if (tile == 'D' && g->config.door.img && g->config.door.data)
		return (&g->config.door);
	if (side == 0 && r->dir_x > 0)
		return (&g->config.west);
	if (side == 0 && r->dir_x < 0)
		return (&g->config.east);
	if (side == 1 && r->dir_y > 0)
		return (&g->config.north);
	return (&g->config.south);
}

void	draw_texture_column(t_game *g, int x, t_texinfo *ti)
{
	double	dist;
	int		tex_x;

	if (ti->side == 0)
		dist = (ti->ray->map_x - g->player.x
				+ (1 - ti->ray->step_x) / 2.0) / ti->ray->dir_x;
	else
		dist = (ti->ray->map_y - g->player.y
				+ (1 - ti->ray->step_y) / 2.0) / ti->ray->dir_y;
	ti->info.height = (int)(HEIGHT / dist);
	ti->info.start = -ti->info.height / 2 + HEIGHT / 2
		+ g->look_offset + g->camera_height;
	ti->info.end = ti->info.height / 2 + HEIGHT / 2
		+ g->look_offset + g->camera_height;
	if (ti->info.start < 0)
		ti->info.start = 0;
	if (ti->info.end >= HEIGHT)
		ti->info.end = HEIGHT - 1;
	ti->tex = get_texture(g, ti->ray, ti->side,
			ti->game->config.map[ti->ray->map_y][ti->ray->map_x]);
	if (!ti->tex || !ti->tex->data || ti->tex->width <= 0
		|| ti->tex->height <= 0)
		exit_error("❌ Invalid texture");
	tex_x = compute_tex_x(ti, dist);
	draw_column_pixels(g, x, ti, tex_x);
}
