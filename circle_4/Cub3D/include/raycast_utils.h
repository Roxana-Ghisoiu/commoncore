/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:23:38 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/21 20:02:46 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_UTILS_H
# define RAYCAST_UTILS_H

# include "cub3d.h"
# include "raycast.h"

typedef struct s_column_info
{
	int	start;
	int	end;
	int	height;
}	t_column_info;

typedef struct s_texinfo
{
	t_game			*game;
	t_ray			*ray;
	int				side;
	char			tile;
	t_texture		*tex;
	t_column_info	info;
}	t_texinfo;

void	perform_dda(t_game *g, t_ray *r, char *tile, int *side);
void	draw_texture_column(t_game *g, int x, t_texinfo *info);
int		compute_tex_x(t_texinfo *ti, double dist);
void	draw_column_pixels(t_game *g, int x, t_texinfo *ti, int tex_x);

#endif
