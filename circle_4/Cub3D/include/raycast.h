/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:23:38 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 19:27:48 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
}	t_ray;

typedef struct s_health_info
{
	int	x;
	int	y;
	int	green;
	int	health;
}	t_health_info;

void	render_walls(t_game *g);
void	init_ray_data(t_ray *r, t_game *g, double cam_x);
void	set_steps(t_ray *r, t_game *g);
double	safe_div(double num);

#endif
