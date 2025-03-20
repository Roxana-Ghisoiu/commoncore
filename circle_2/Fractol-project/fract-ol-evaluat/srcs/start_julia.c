/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_julia.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:12:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 16:16:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Initializes the MLX instance and image for fractal rendering.
 */
void	init_mlx(t_fractol *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
	{
		free(fractal);
		ft_putendl_fd("Error: MLX initialization failed", 2);
		exit(EXIT_FAILURE);
	}
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	fractal->data = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->size_line, &fractal->endian);
}

/**
 * @brief    Starts the Julia fractal.
 */
void	start_julia(double cx, double cy)
{
	t_fractol	*fractal;

	fractal = malloc(sizeof(t_fractol));
	if (!fractal)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		exit(EXIT_FAILURE);
	}
	fractal->cx = cx;
	fractal->cy = cy;
	fractal->name = "julia";
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 100;
	fractal->color = 0xFFFFFF;
	//init_mlx(fractal);
	printf("Start Julia with cx = %f, cy = %f\n", fractal->cx, fractal->cy);
	start_fractal(fractal, "Julia", draw_julia);
}
