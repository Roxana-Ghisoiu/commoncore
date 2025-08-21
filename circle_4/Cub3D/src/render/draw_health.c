/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:46:24 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 18:52:20 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_utils.h"
#include "raycast.h"

#define BAR_WIDTH 100
#define BAR_HEIGHT 10

void	draw_health_fg(t_game *g, t_health_info info)
{
	int	i;
	int	j;
	int	width;

	width = (info.health * BAR_WIDTH) / 100;
	j = -1;
	while (++j < BAR_HEIGHT)
	{
		i = -1;
		while (++i < width)
			set_pixel(&g->frame, info.x + i, info.y + j, info.green);
	}
}
