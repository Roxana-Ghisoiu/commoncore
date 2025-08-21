/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:25:38 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 01:24:21 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

# include "cub3d.h"

// Forward declarations
typedef struct s_game			t_game;
typedef struct s_enemy			t_enemy;
typedef struct s_enemy_bounds	t_enemy_bounds;

// Enemy rendering
void	calculate_transform(t_game *g, t_enemy *e,
			double *tx, double *ty);
void	clip_enemy_bounds(t_game *g, double ty, int screen_x,
			t_enemy_bounds *b);
void	draw_enemy_stripe(t_game *g, t_enemy *e,
			int stripe, t_enemy_bounds *b);
int		render_one_enemy(t_game *g, t_enemy *e);

// Enemy logic
void	update_enemies(t_game *g);

#endif
