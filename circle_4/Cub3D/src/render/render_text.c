/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:58:57 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/20 16:43:42 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <string.h>

void	draw_text_centered(t_game *game, const char *text, int y, int color)
{
	int	text_width;
	int	x;
	int	dx;
	int	dy;

	if (!text || !game || !game->mlx || !game->win)
		return ;
	text_width = strlen(text) * 10;
	x = (WIDTH - text_width) / 2;
	dy = -2;
	while (++dy <= 1)
	{
		dx = -2;
		while (++dx <= 1)
		{
			mlx_string_put(
				game->mlx, game->win, x + dx, y + dy, color, (char *)text);
		}
	}
}
