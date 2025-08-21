/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:26:50 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 16:26:13 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

void	parse_config(t_game *game, char *filename);
int		parse_rgb(const char *str);
char	**append_map_line(char **map, char *line);
void	find_player_spawn(t_game *game);
bool	is_map_line(char *line);
void	parse_color_or_texture(char *line, t_config *config);
void	read_and_parse_lines(t_game *game, int fd);
char	*read_line(int fd);
void	parse_texture_line(char *line, t_game *game);
void	set_dir_n_s(t_game *game, char dir, double fov);
void	set_dir_e_w(t_game *game, char dir, double fov);

#endif
