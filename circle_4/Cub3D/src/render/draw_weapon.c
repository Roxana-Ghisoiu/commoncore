/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:07:48 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 18:42:09 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_utils.h"

void	draw_weapon(t_game *game)
{
	int	x;
	int	y;
	int	color;
	int	w_x;
	int	w_y;

	w_x = (WIDTH - game->weapon.width) / 2;
	w_y = HEIGHT - game->weapon.height;
	y = -1;
	while (++y < game->weapon.height)
	{
		x = -1;
		while (++x < game->weapon.width)
		{
			color = get_pixel_color(&game->weapon, x, y);
			if (color == 0xFF00FF)
				continue ;
			set_pixel(&game->frame, w_x + x, w_y + y, color);
		}
	}
}
