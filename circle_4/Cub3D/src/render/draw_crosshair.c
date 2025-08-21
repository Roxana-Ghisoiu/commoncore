/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:08:46 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/21 20:12:07 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_utils.h"
#include <math.h>

static void	draw_crosshair_lines(t_game *game, int cx, int cy, int color)
{
	int	i;
	int	size;

	size = 6;
	i = -size - 1;
	while (++i <= size)
	{
		set_pixel(&game->frame, cx + i, cy, color);
		set_pixel(&game->frame, cx, cy + i, color);
	}
}

void	draw_crosshair(t_game *game)
{
	int		center_x;
	int		center_y;
	double	t;
	int		brightness;
	int		color;

	center_x = WIDTH / 2;
	center_y = HEIGHT - game->weapon.height - 20;
	t = game->frame_count * 0.1;
	brightness = (int)((sin(t) + 1.0) * 0.5 * 255);
	color = (brightness << 16);
	draw_crosshair_lines(game, center_x, center_y, color);
}
