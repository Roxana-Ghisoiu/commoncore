/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mandelbrot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:12:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 16:15:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Starts the Mandelbrot fractal.
 */
void	start_mandelbrot(void)
{
	t_fractol	*fractal;

	fractal = malloc(sizeof(t_fractol));
	if (!fractal)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		exit(EXIT_FAILURE);
	}
	fractal->name = "mandelbrot";
	start_fractal(fractal, "Mandelbrot", draw_mandelbrot);
}
