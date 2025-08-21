/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_norm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:26:29 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 01:48:07 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycast.h"
#include <math.h>

double	safe_div(double num)
{
	if (num == 0)
		return (1e30);
	return (fabs(1.0 / num));
}

void	init_ray_data(t_ray *r, t_game *g, double cam_x)
{
	r->dir_x = g->player.dir_x + g->player.plane_x * cam_x;
	r->dir_y = g->player.dir_y + g->player.plane_y * cam_x;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	r->delta_x = safe_div(r->dir_x);
	r->delta_y = safe_div(r->dir_y);
}

void	set_steps(t_ray *r, t_game *g)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->player.x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - g->player.x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (g->player.y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - g->player.y) * r->delta_y;
	}
}
