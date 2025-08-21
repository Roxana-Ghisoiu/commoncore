/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:39:21 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 19:46:20 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <mlx.h>

static void	free_config_paths(t_game *g)
{
	if (g->config.north_texture)
		free(g->config.north_texture);
	if (g->config.south_texture)
		free(g->config.south_texture);
	if (g->config.east_texture)
		free(g->config.east_texture);
	if (g->config.west_texture)
		free(g->config.west_texture);
	if (g->config.ceiling_texture)
		free(g->config.ceiling_texture);
	if (g->config.floor_texture)
		free(g->config.floor_texture);
}

void	clean_textures(t_game *g)
{
	if (g->config.north.img)
		mlx_destroy_image(g->mlx, g->config.north.img);
	if (g->config.south.img)
		mlx_destroy_image(g->mlx, g->config.south.img);
	if (g->config.east.img)
		mlx_destroy_image(g->mlx, g->config.east.img);
	if (g->config.west.img)
		mlx_destroy_image(g->mlx, g->config.west.img);
	if (g->config.door.img)
		mlx_destroy_image(g->mlx, g->config.door.img);
	if (g->config.ceiling_tex.img)
		mlx_destroy_image(g->mlx, g->config.ceiling_tex.img);
	if (g->config.floor_tex.img)
		mlx_destroy_image(g->mlx, g->config.floor_tex.img);
}

void	clean_exit(t_game *g, int code)
{
	int	i;

	if (g->frame.img)
		mlx_destroy_image(g->mlx, g->frame.img);
	if (g->weapon.img)
		mlx_destroy_image(g->mlx, g->weapon.img);
	clean_textures(g);
	free_config_paths(g);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	if (g->config.map)
	{
		i = 0;
		while (g->config.map[i])
			free(g->config.map[i++]);
		free(g->config.map);
	}
	exit(code);
}
