/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:00:00 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 14:23:08 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	add_door_timer(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->num_open_doors)
	{
		if (g->door_timers[i].x == x && g->door_timers[i].y == y)
			return ;
		i++;
	}
	if (g->num_open_doors < MAX_DOORS)
	{
		g->door_timers[g->num_open_doors].x = x;
		g->door_timers[g->num_open_doors].y = y;
		g->door_timers[g->num_open_doors].open_time = get_current_time();
		g->num_open_doors++;
	}
}

void	interact_with_door(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.x + game->player.dir_x);
	y = (int)(game->player.y + game->player.dir_y);
	if (x < 0 || y < 0
		|| y >= game->config.map_height
		|| x >= game->config.map_width)
		return ;
	if (game->config.map[y][x] == 'D')
	{
		game->config.map[y][x] = 'O';
		add_door_timer(game, x, y);
	}
	else if (game->config.map[y][x] == 'O')
		game->config.map[y][x] = 'D';
}

void	check_auto_close_doors(t_game *g)
{
	double			now;
	int				i;
	t_door_timer	*d;

	now = get_current_time();
	i = 0;
	while (i < g->num_open_doors)
	{
		d = &g->door_timers[i];
		if (now - d->open_time >= 3.0)
		{
			if (g->config.map[d->y][d->x] == 'O')
				g->config.map[d->y][d->x] = 'D';
			g->door_timers[i] = g->door_timers[g->num_open_doors - 1];
			g->num_open_doors--;
		}
		else
			i++;
	}
}
