/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 15:56:59 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Closes the window and exits the program.
 *
 * @param    fractal    The fractal structure containing the necessary data.
 */
int	close_window(t_fractol *fractal)
{
	if (fractal->img)
		mlx_destroy_image(fractal->mlx, fractal->img);
	if (fractal->win)
		mlx_destroy_window(fractal->mlx, fractal->win);
	mlx_destroy_display(fractal->mlx);
	if (fractal->mlx)
	{
		mlx_loop_end(fractal->mlx);
		free(fractal->mlx);
		fractal->mlx = NULL;
	}
	free(fractal);
	exit(0);
	return (0);
}
