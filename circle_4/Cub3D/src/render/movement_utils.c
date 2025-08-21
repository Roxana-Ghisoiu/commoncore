/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:18:22 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 19:57:51 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "types.h"

int	is_walkable_tile(char tile)
{
	if (tile == '0' || tile == 'O')
		return (1);
	return (0);
}

int	is_walkable(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->config.map_height)
		return (0);
	if (map_x < 0 || map_x >= game->config.map_width)
		return (0);
	if (game->config.map[map_y][map_x] == '1')
		return (0);
	return (1);
}

t_vec2	get_direction_to_player(t_game *g, double ex, double ey)
{
	t_vec2	dir;

	dir.x = g->player.x - ex;
	dir.y = g->player.y - ey;
	return (dir);
}

bool	has_line_of_sight(t_game *g, double ex, double ey)
{
	t_vec2	dir;
	t_vec2	step;
	t_vec2	pos;

	dir = get_direction_to_player(g, ex, ey);
	step = get_step_vector(dir.x, dir.y);
	pos.x = ex;
	pos.y = ey;
	while ((int)pos.x != (int)g->player.x || (int)pos.y != (int)g->player.y)
	{
		if (g->config.map[(int)pos.y][(int)pos.x] == '1')
			return (false);
		pos.x += step.x;
		pos.y += step.y;
	}
	return (true);
}

t_vec2	get_step_vector(double dx, double dy)
{
	t_vec2	step;
	double	dist;

	dist = sqrt(dx * dx + dy * dy);
	if (dist == 0)
	{
		step.x = 0;
		step.y = 0;
	}
	else
	{
		step.x = dx / dist * 0.1;
		step.y = dy / dist * 0.1;
	}
	return (step);
}
