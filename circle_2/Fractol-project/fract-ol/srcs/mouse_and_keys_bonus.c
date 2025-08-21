/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_keys_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:01:13 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 15:01:27 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Zooms in or out while keeping the mouse position fixed.
 */
void	zoom(t_fractol *fractal, int direction, int x, int y)
{
	double	zoom_factor;
	double	mouse_x;
	double	mouse_y;

	if (direction == 1)
		zoom_factor = 1.2;
	else if (direction == -1)
		zoom_factor = 0.8;
	else
		return ;
	mouse_x = fractal->offset_x + (x - WIDTH / 2) * (4.0 / (fractal->zoom
				* WIDTH));
	mouse_y = fractal->offset_y + (y - HEIGHT / 2) * (4.0 / (fractal->zoom
				* HEIGHT));
	fractal->zoom *= zoom_factor;
	fractal->offset_x = mouse_x - (x - WIDTH / 2) * (4.0 / (fractal->zoom
				* WIDTH));
	fractal->offset_y = mouse_y - (y - HEIGHT / 2) * (4.0 / (fractal->zoom
				* HEIGHT));
}
