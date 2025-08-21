/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:30:00 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 03:08:36 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "cub3d.h"

int		is_door(char tile);
int		is_closed_door(char tile);
int		is_open_door(char tile);
void	interact_with_door(t_game *game);
void	check_auto_close_doors(t_game *g);
double	get_current_time(void);

#endif