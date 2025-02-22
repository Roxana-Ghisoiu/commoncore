/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/21 15:45:51 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Initializes the MiniLibX and creates the window and image.
 *
 * @param    fractal    The fractal structure containing the necessary data.
 * @param    title      The title of the window.
 */
void	init_and_create_window(t_fractol *fractal, const char *title)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
	{
		ft_putendl_fd("Error: MiniLibX initialization failed", 2);
		free(fractal);
		exit(EXIT_FAILURE);
	}
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, (char *)title);
	if (!fractal->win)
	{
		ft_putendl_fd("Error: Window creation failed", 2);
		free(fractal->mlx);
		free(fractal);
		exit(EXIT_FAILURE);
	}
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		ft_putendl_fd("Error: Image creation failed", 2);
		mlx_destroy_window(fractal->mlx, fractal->win);
		free(fractal->mlx);
		free(fractal);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief    Initializes the image data.
 *
 * @param    fractal    The fractal structure containing the necessary data.
 */
void	init_image_data(t_fractol *fractal)
{
	fractal->data = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->size_line, &fractal->endian);
	if (!fractal->data)
	{
		ft_putendl_fd("Error: Image data allocation failed", 2);
		mlx_destroy_image(fractal->mlx, fractal->img);
		mlx_destroy_window(fractal->mlx, fractal->win);
		free(fractal->mlx);
		free(fractal);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief    Initializes and starts a fractal window.
 */
void	start_fractal(t_fractol *fractal, const char *title,
		void (*draw_func)(t_fractol *))
{
	init_and_create_window(fractal, title);
	init_image_data(fractal);
	init_fractal(fractal);
	mlx_key_hook(fractal->win, key_hook, fractal);
	mlx_mouse_hook(fractal->win, mouse_hook, fractal);
	mlx_hook(fractal->win, 17, 0, close_window, fractal);
	draw_func(fractal);
	mlx_loop(fractal->mlx);
}
