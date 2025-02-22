/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:47:10 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/22 16:58:16 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "LibftPrintf/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# define WIDTH 800
# define HEIGHT 600
# define NUM_THREADS 4  // Numărul de fire de execuție

// Key codes for Linux (X11)
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define R 114
# define C 99
# define J 106
# define P 112
# define M 109

// Mouse events
# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	double	zoom;			// Factor of zoom
	double	offset_x;		// Offset on X axis
	double	offset_y;		// Offset on Y axis
	double	cx;			// Julia set component
	double	cy;			// Julia set component
	int		color;			// Fractal drawing color
	int		max_iterations;	// Maximum iterations for fractal calculation
	char	*name;			// Name of the fractal to draw
	pthread_t threads[NUM_THREADS]; // Fire de execuție
}			t_fractol;

typedef struct s_complex
{
	double	re;
	double	im;
}			t_complex;

typedef struct s_julia_vars
{
	double	z_re;
	double	z_im;
	double	c_re;
	double	c_im;
	int		max_iterations;
}			t_julia_vars;

typedef struct s_vars
{
	double	c_re;
	double	c_im;
	double	z_re;
	double	z_im;
	double	tmp;
	int		iteration;
}			t_vars;

// Function declarations from main.c
void	print_usage(void);

// Function declarations from fractol.c
int	get_color(int iteration, int max_iteration, int base_color);
void	draw_fractal(t_fractol *fractol, const char *name);

// Function declarations from start_fractals.c
void	start_fractal(t_fractol *fractal, const char *title,
			void (*draw_func)(t_fractol *));
void	init_and_create_window(t_fractol *fractal, const char *title);
void	init_image_data(t_fractol *fractal);

// Function declarations from start_fractal_bonus.c
void	start_fractal_bonus(void);

// Function declarations from fractal_bonus.c
void	init_vars(t_fractol *f, t_vars *v, int x, int y);
void	calculate_fractal(t_fractol *f, t_vars *v);
void	draw_fractal_bonus(t_fractol *f);

// Function declarations from utils.c
int		close_window(t_fractol *fractal);

// Function declarations from event.c
int		key_hook(int key_code, t_fractol *fractal);
int		mouse_hook(int mouse_code, int x, int y, t_fractol *fractal);

// Function declarations from start_mandelbrot.c
void	start_mandelbrot(void);

// Function declarations from mandelbrot.c
void	init_mandelbrot_vars(t_fractol *fractol, int x, int y,
			t_complex *c);
int		mandelbrot_iterations(double c_re, double c_im, int max_iterations);
void	draw_mandelbrot_pixel(t_fractol *fractol, int x, int y,
			int iteration);
void	draw_mandelbrot(t_fractol *fractol);

// Function declarations from start_julia.c
void	start_julia(double cx, double cy);
void    init_mlx (t_fractol *fractal);

// Function declarations for julia.c
void	init_julia_vars(t_fractol *fractol, int x, int y,
			t_julia_vars *vars);
int		julia_iterations(t_julia_vars *vars);
void	draw_julia_pixel(t_fractol *fractal, int x, int y, int iteration);
void	draw_julia(t_fractol *fractal);

// Function declarations for mouse_and_keys.c
void	change_iterations(t_fractol *fractal, int key_code);
void	init_fractal(t_fractol *fractal);
double	generate_random_c (void);
int		handle_mouse(int button, int x, int y, t_fractol *fractal);
void	set_random_julia(double *cx, double *cy);

// Function declarations for mouse_and_keys_bonus.c
void	zoom(t_fractol *fractal, int direction, int x, int y);

#endif
