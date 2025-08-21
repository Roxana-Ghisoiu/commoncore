/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:37:23 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 19:41:48 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_UTILS_H
# define MOVEMENT_UTILS_H

# include "cub3d.h"

t_vec2	get_direction_to_player(t_game *g, double ex, double ey);
t_vec2	get_step_vector(double dx, double dy);
int		is_walkable(t_game *game, double x, double y);
bool	has_line_of_sight(t_game *g, double ex, double ey);

#endif