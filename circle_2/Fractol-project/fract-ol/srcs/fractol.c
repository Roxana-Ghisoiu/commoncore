/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/21 15:45:51 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_color(int iteration, int max_iteration, int base_color)
{
	int		color;
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)iteration / (double)max_iteration;
	r = ((base_color >> 16) & 0xFF) * t
		+ (int)(9 * (1 - t) * t * t * t * 255);
	g = ((base_color >> 8) & 0xFF) * t
		+ (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (base_color & 0xFF) * t
		+ (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

/**
 * @brief    Draws the appropriate fractal based on the name.
 *
 * @param    fractol    The fractol structure containing the necessary data.
 * @param    name       The name of the fractal to draw.
 */
void	draw_fractal(t_fractol *fractol, const char *name)
{
	if (ft_strncmp(name, "mandelbrot", 10) == 0)
		draw_mandelbrot(fractol);
	else if (ft_strncmp(name, "julia", 5) == 0)
		draw_julia(fractol);
	else if (ft_strncmp(name, "fractal_bonus", 13) == 0)
		draw_fractal_bonus(fractol);
}
