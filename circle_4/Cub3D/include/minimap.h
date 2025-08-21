/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:38:38 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/21 13:39:24 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

void	draw_tile(t_game *g, int x, int y, int color);
void	draw_player_square(t_game *g, int cx, int cy);
void	draw_player_direction(t_game *g, int cx, int cy);
void	draw_minimap(t_game *game);
int		map_height(t_game *game);
int		map_width(t_game *game);

#endif
