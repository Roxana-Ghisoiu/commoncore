/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:38:50 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/21 11:16:02 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include "render.h"

int	handle_close(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}

void	start_game(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->win);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}
