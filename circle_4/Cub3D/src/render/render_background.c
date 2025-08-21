/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:19:20 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 03:06:16 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_utils.h"

static void	draw_ceiling(t_game *game, int *data, int horizon)
{
	int	x;
	int	y;

	y = -1;
	while (++y < horizon)
	{
		x = -1;
		while (++x < WIDTH)
			data[y * WIDTH + x] = game->config.ceiling_color;
	}
}

static void	draw_floor(t_game *game, int *data, int horizon)
{
	int	x;
	int	y;

	y = horizon - 1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			data[y * WIDTH + x] = game->config.floor_color;
	}
}

void	render_background(t_game *game, int *data)
{
	int	horizon;

	horizon = HEIGHT / 2 + game->look_offset + game->camera_height;
	draw_ceiling(game, data, horizon);
	draw_floor(game, data, horizon);
}
