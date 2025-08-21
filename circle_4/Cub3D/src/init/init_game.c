/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:21:58 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 16:22:51 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parse.h"
#include "string_utils.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error("Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		exit_error("Failed to create window");
}

void	init_frame_buffer(t_game *game)
{
	game->frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame.img)
		exit_error("Failed to create main image buffer");
	game->frame.addr = mlx_get_data_addr(game->frame.img,
			&game->frame.bpp,
			&game->frame.line_len,
			&game->frame.endian);
	game->frame.width = WIDTH;
	game->frame.height = HEIGHT;
}

static void	init_defaults(t_game *game)
{
	memset(&game->keys, 0, sizeof(t_keys));
	game->minimap_enabled = 1;
	game->frame_count = 0;
	game->health = 100;
	game->lives = 3;
	game->look_offset = 0;
	game->num_enemies = 0;
	game->num_open_doors = 0;
	memset(game->door_timers, 0, sizeof(game->door_timers));
}

void	init_game(t_game *game, char *map_file)
{
	init_defaults(game);
	parse_config(game, map_file);
	init_mlx(game);
	init_frame_buffer(game);
	load_environment_textures(game);
	load_weapon(game);
	load_enemy_textures(game);
}
