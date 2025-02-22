/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roxana-Ghisoiu <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:06:02 by Roxana-Ghisoiu    #+#    #+#             */
/*   Updated: 2025/02/22 14:58:42 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>

/**
 * @brief    Prints the usage instructions and exits the program.
 */

void	print_usage(void)
{
	ft_putendl_fd("Usage: ./fractol <fractal_name> [cx cy]", 1);
	ft_putendl_fd("Av fract: mandelbrot, julia [cx cy],fractal_bonus", 1);
	exit(EXIT_FAILURE);
}

/**
* @brief    The main function of the program.
It checks the arguments and starts the appropriate fractal.
 */

int	main(int argc, char **argv)
{
	double	cx;
	double	cy;

	if (argc < 2 || argc > 4)
		print_usage();
	if (ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot") + 1) == 0)
		start_mandelbrot();
	else if (ft_strncmp(argv[1], "julia", ft_strlen("julia") + 1) == 0)
	{
		cx = -0.7;
		cy = 0.27015;
		if (argc == 4)
		{
			cx = strtod(argv[2], NULL);
			cy = strtod(argv[3], NULL);
		}
		start_julia(cx, cy);
	}
	else if (ft_strncmp(argv[1], "fractal_bonus", ft_strlen("fractal_bonus")
			+ 1) == 0)
		start_fractal_bonus();
	else
		print_usage();
	return (0);
}
