/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:05:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 15:05:29 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Initializes variables for Mandelbrot set calculations.
 */
void	init_mandelbrot_vars(t_fractol *fractol, int x, int y, t_complex *c)
{
	c->re = 1.5 * (x - WIDTH / 2) / (0.5 * fractol->zoom * WIDTH)
		+ fractol->offset_x;
	c->im = (y - HEIGHT / 2) / (0.5 * fractol->zoom * HEIGHT)
		+ fractol->offset_y;
}

/**

* @brief: Calculates the number of iterations
 for a given point in the Mandelbrot set.
 */
int	mandelbrot_iterations(double c_re, double c_im, int max_iterations)
{
	double	z_re;
	double	z_im;
	double	tmp;
	int		iteration;

	z_re = 0;
	z_im = 0;
	iteration = 0;
	while (z_re * z_re + z_im * z_im < 4 && iteration < max_iterations)
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		iteration++;
	}
	return (iteration);
}

/**
 * @brief    Draws a single pixel for the Mandelbrot set.
 */
void	draw_mandelbrot_pixel(t_fractol *fractol, int x, int y, int iteration)
{
	int	pixel;
	int	color;

	color = get_color(iteration, fractol->max_iterations, fractol->color);
	pixel = (y * fractol->size_line) + (x * (fractol->bpp / 8));
	if (pixel >= 0 && pixel + 2 < WIDTH * HEIGHT * (fractol->bpp / 8))
	{
		fractol->data[pixel] = color & 0xFF;
		fractol->data[pixel + 1] = (color >> 8) & 0xFF;
		fractol->data[pixel + 2] = (color >> 16) & 0xFF;
	}
}

/**
 * @brief    Draws the Mandelbrot fractal.
 */
void	draw_mandelbrot(t_fractol *fractol)
{
	int			x;
	int			y;
	int			iteration;
	t_complex	c;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			init_mandelbrot_vars(fractol, x, y, &c);
			iteration = mandelbrot_iterations(c.re, c.im,
					fractol->max_iterations);
			draw_mandelbrot_pixel(fractol, x, y, iteration);
			x++;
		}
		y++;
	}
	mlx_clear_window(fractol->mlx, fractol->win);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
