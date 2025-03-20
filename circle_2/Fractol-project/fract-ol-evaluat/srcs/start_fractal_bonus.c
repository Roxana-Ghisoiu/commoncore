/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fractal_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:14:48 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 16:15:01 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Starts the bonus fractal.
 */
void	start_fractal_bonus(void)
{
	t_fractol	*fractal;

	fractal = malloc(sizeof(t_fractol));
	if (!fractal)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		exit(EXIT_FAILURE);
	}
	fractal->name = "fractal_bonus";
	start_fractal(fractal, "Fractal Bonus", draw_fractal_bonus);
}
