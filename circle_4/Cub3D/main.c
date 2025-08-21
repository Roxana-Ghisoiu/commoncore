/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:20:20 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 01:56:05 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (exit_error("Usage: ./cub3D map.cub"));
	ft_memset(&game, 0, sizeof(t_game));
	init_game(&game, argv[1]);
	start_game(&game);
	clean_exit(&game, 0);
	return (0);
}
