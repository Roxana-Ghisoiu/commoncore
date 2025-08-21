/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:16:49 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 16:22:55 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_game *game, t_texture *tex, char *path)
{
	int	bpp;
	int	line_len;
	int	endian;

	if (!path || access(path, F_OK) != 0)
	{
		write(2, "❌ Texture not found: ", 22);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		exit_error("Missing texture file");
	}
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		exit_error("mlx_xpm_file_to_image failed");
	tex->data = (int *)mlx_get_data_addr(tex->img,
			&bpp, &line_len, &endian);
	if (!tex->data)
		exit_error("mlx_get_data_addr failed");
}

void	load_environment_textures(t_game *game)
{
	if (!game->config.north_texture || !game->config.south_texture
		|| !game->config.east_texture || !game->config.west_texture)
		exit_error("Missing one or more texture paths in .cub file");
	load_texture(game, &game->config.north, game->config.north_texture);
	load_texture(game, &game->config.south, game->config.south_texture);
	load_texture(game, &game->config.east, game->config.east_texture);
	load_texture(game, &game->config.west, game->config.west_texture);
	load_texture(game, &game->config.door, "./textures/door.xpm");
	load_texture(game, &game->config.game_over, "./textures/gameover.xpm");
	if (!game->config.door.img)
		exit_error("Failed to load door.xpm — check path or file");
	if (game->config.ceiling_texture
		&& ends_with(game->config.ceiling_texture, ".xpm"))
	{
		game->config.ceiling_from_texture = 1;
		load_texture(game, &game->config.ceiling_tex,
			game->config.ceiling_texture);
	}
	if (game->config.floor_texture
		&& ends_with(game->config.floor_texture, ".xpm"))
	{
		game->config.floor_from_texture = 1;
		load_texture(game, &game->config.floor_tex,
			game->config.floor_texture);
	}
}

void	load_weapon(t_game *game)
{
	game->weapon.img = mlx_xpm_file_to_image(game->mlx, "textures/weapon.xpm",
			&game->weapon.width, &game->weapon.height);
	if (!game->weapon.img)
		exit_error("Failed to load weapon.xpm — check path or file");
	game->weapon.addr = mlx_get_data_addr(game->weapon.img,
			&game->weapon.bpp,
			&game->weapon.line_len,
			&game->weapon.endian);
}

void	load_enemy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		load_texture(game, &game->enemies[i].texture, "./textures/enemy.xpm");
		printf("👾 Enemy %d texture loaded: %dx%d\n", i,
			game->enemies[i].texture.width, game->enemies[i].texture.height);
		i++;
	}
}
