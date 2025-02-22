/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roxana-Ghisoiu <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:11:52 by Roxana-Ghisoiu    #+#    #+#             */
/*   Updated: 2025/02/21 13:50:03 by Roxana-Ghisoiu   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Handles keyboard input for fractal manipulation.
 *
 * @param    key_code  The key pressed.
 * @param    fractal   The fractal structure containing the necessary data.
 */
int	key_hook(int key_code, t_fractol *fractal)
{
	if (key_code == ESC)
		close_window(fractal);
	else if (key_code == LEFT)
		fractal->offset_x -= 0.1 / fractal->zoom;
	else if (key_code == RIGHT)
		fractal->offset_x += 0.1 / fractal->zoom;
	else if (key_code == UP)
		fractal->offset_y -= 0.1 / fractal->zoom;
	else if (key_code == DOWN)
		fractal->offset_y += 0.1 / fractal->zoom;
	else if (key_code == R)
		init_fractal(fractal);
	else if (key_code == C)
	{
		fractal->color += 0x050505;
		if (fractal->color > 0xFFFFFF)
			fractal->color = 0;
	}
	else if (key_code == J)
		set_random_julia(&fractal->cx, &fractal->cy);
	else if (key_code == M || key_code == P)
		change_iterations(fractal, key_code);
	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, fractal->name);
	return (0);
}

/**
 * @brief    Handles mouse input for zooming.
 *
 * @param    mouse_code The mouse event.
 * @param    x          The x coordinate of the mouse.
 * @param    y          The y coordinate of the mouse.
 * @param    fractal    The fractal structure containing the necessary data.
 */
int	mouse_hook(int mouse_code, int x, int y, t_fractol *fractal)
{
	if (mouse_code == SCROLL_UP)
		zoom(fractal, 1, x, y);
	else if (mouse_code == SCROLL_DOWN)
		zoom(fractal, -1, x, y);
	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, fractal->name);
	return (0);
}
