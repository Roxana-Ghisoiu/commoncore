/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 20:08:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Initializes the variables for the Julia set calculations.
 */
void	init_julia_vars(t_fractol *fractal, int x, int y, t_julia_vars *vars)
{
	vars->z_re = 1.5 * (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH)
		+ fractal->offset_x;
	vars->z_im = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT)
		+ fractal->offset_y;
	vars->c_re = fractal->cx;
	vars->c_im = fractal->cy;
	vars->max_iterations = fractal->max_iterations;
}

/**

* @brief Calculates the number of iterations 
* for a given point in the Julia set.
 */
int	julia_iterations(t_julia_vars *vars)
{
	double	tmp;
	int		iteration;

	iteration = 0;
	while (vars->z_re * vars->z_re + vars->z_im * vars->z_im < 4
		&& iteration < vars->max_iterations)
	{
		if (iteration > 10000)
		{
			printf("Warning: Too many iterations! Breaking loop.\n");
			break ;
		}
		tmp = vars->z_re * vars->z_re - vars->z_im * vars->z_im + vars->c_re;
		vars->z_im = 2 * vars->z_re * vars->z_im + vars->c_im;
		vars->z_re = tmp;
		iteration++;
	}
	return (iteration);
}

/**
 * @brief Draws a single pixel for the Julia set.
 */
void	draw_julia_pixel(t_fractol *fractal, int x, int y, int iteration)
{
	int	pixel;
	int	color;

	color = get_color(iteration, fractal->max_iterations, fractal->color);
	pixel = (y * fractal->size_line) + (x * (fractal->bpp / 8));
	if (pixel >= 0 && pixel + 2 < WIDTH * HEIGHT * (fractal->bpp / 8))
	{
		fractal->data[pixel] = color & 0xFF;
		fractal->data[pixel + 1] = (color >> 8) & 0xFF;
		fractal->data[pixel + 2] = (color >> 16) & 0xFF;
	}
}

/**
 * @brief Draws the Julia fractal.
 */
void	draw_julia(t_fractol *fractal)
{
	int				x;
	int				y;
	int				iteration;
	t_julia_vars	vars;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			init_julia_vars(fractal, x, y, &vars);
			iteration = julia_iterations(&vars);
			draw_julia_pixel(fractal, x, y, iteration);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}
