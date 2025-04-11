/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roxana-Ghisoiu <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:40:28 by Roxana-Ghisoiu    #+#    #+#             */
/*   Updated: 2025/02/21 13:50:03 by Roxana-Ghisoiu   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Changes the number of iterations for the fractal.
 */
void	change_iterations(t_fractol *fractol, int key_code)
{
	if (key_code == P)
		fractol->max_iterations += 10;
	else if (key_code == M && fractol->max_iterations > 10)
		fractol->max_iterations -= 10;
}

/**
 * @brief    Initializes the fractal structure with default values.
 */
void	init_fractal(t_fractol *fractal)
{
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iterations = 100;
	fractal->color = 0xFFFFFF;
	if (ft_strncmp(fractal->name, "julia", 6) != 0)
	{
		fractal->cx = -0.7;
		fractal->cy = 0.27015;
	}
}

/**
 * @brief    Generates a random constant for Julia set.
 */
double	generate_random_c(void)
{
	return ((double)rand() / (double)RAND_MAX * 2.0 - 1.0);
}

/**
 * @brief    Handles mouse events for zooming.
 */
int	handle_mouse(int button, int x, int y, t_fractol *fractal)
{
	if (button == SCROLL_UP)
		zoom(fractal, 1, x, y);
	else if (button == SCROLL_DOWN)
		zoom(fractal, -1, x, y);
	mlx_clear_window(fractal->mlx, fractal->win);
	draw_fractal(fractal, fractal->name);
	return (0);
}

/**
 * @brief    Sets the constants of Julia to random values.
 */
void	set_random_julia(double *cx, double *cy)
{
	*cx = generate_random_c();
	*cy = generate_random_c();
}
