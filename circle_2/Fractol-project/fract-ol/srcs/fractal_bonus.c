/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:58:22 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/21 09:58:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Initializes the variables for the fractal calculation.
 */
void	init_vars(t_fractol *f, t_vars *v, int x, int y)
{
	v->c_re = 1.5 * (x - WIDTH / 2) / (0.5 * f->zoom * WIDTH) + f->offset_x;
	v->c_im = (y - HEIGHT / 2) / (0.5 * f->zoom * HEIGHT) + f->offset_y;
	v->z_re = 0;
	v->z_im = 0;
	v->iteration = 0;
}

/**
 * @brief    Calculates the fractal for a given pixel.
 */
void	calculate_fractal(t_fractol *f, t_vars *v)
{
	while (v->z_re * v->z_re + v->z_im * v->z_im < 4
		&& v->iteration < f->max_iterations)
	{
		v->tmp = v->z_re * v->z_re - v->z_im * v->z_im + v->c_re;
		v->z_im = -2 * v->z_re * v->z_im + v->c_im;
		v->z_re = v->tmp;
		v->iteration++;
	}
}

/**
 * @brief    Draws the Tricorn (Anti-Mandelbrot) fractal.
 */
void	draw_fractal_bonus(t_fractol *f)
{
	t_vars	vars;
	int		color;
	int		pixel;
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			init_vars(f, &vars, x, y);
			calculate_fractal(f, &vars);
			color = get_color(vars.iteration, f->max_iterations, f->color);
			pixel = (y * f->size_line) + (x * (f->bpp / 8));
			f->data[pixel] = color & 0xFF;
			f->data[pixel + 1] = (color >> 8) & 0xFF;
			f->data[pixel + 2] = (color >> 16) & 0xFF;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
