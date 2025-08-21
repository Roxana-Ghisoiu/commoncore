/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:50:00 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 03:10:13 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_UTILS_H
# define PARSE_MAP_UTILS_H

# include "cub3d.h"

int		get_max_line_length(char **map, int count, const char *new_line);
void	copy_old_lines(char **new_map, char **map, int count, int max_len);
void	add_last_line(char **new_map, int count, char *line, int max_len);
void	set_dir_n_s(t_game *game, char dir, double fov);
void	set_dir_e_w(t_game *game, char dir, double fov);
void	set_player_direction(t_game *game, char dir);

#endif
