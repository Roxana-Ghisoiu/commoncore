/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:22:48 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 18:55:43 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include "cub3d.h"

int		get_pixel_color(t_img *img, int x, int y);
void	set_pixel(t_img *img, int x, int y, int color);
void	draw_text_centered(t_game *game, const char *text, int y, int color);

#endif
