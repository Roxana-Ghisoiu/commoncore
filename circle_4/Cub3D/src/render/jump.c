/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:54:43 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 18:54:45 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_jump(t_game *g)
{
	static const double	jump_duration = 0.9;
	static const double	jump_height = 80.0;
	double				t;
	double				normalized_time;
	double				offset;

	t = 1.0 / 60.0;
	g->jump_time += t;
	if (g->jump_time >= jump_duration)
	{
		g->is_jumping = 0;
		g->jump_time = 0;
		g->camera_height = 0;
	}
	else
	{
		normalized_time = g->jump_time / jump_duration;
		offset = -4 * jump_height
			* (normalized_time - 0.5) * (normalized_time - 0.5)
			+ jump_height;
		g->camera_height = (int)offset;
	}
}
