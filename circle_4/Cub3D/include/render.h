/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:56:36 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 19:07:29 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

void	render_background(t_game *game, int *data);
void	load_texture(t_game *game, t_texture *tex, char *path);
void	draw_gradient_sky(int *data, int frame);
void	draw_minimap(t_game *game);
void	draw_weapon(t_game *game);
void	draw_text_centered(t_game *game, const char *text, int y, int color);

#endif
