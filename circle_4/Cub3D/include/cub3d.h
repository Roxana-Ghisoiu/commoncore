/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:22:39 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 03:12:09 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 800
# define HEIGHT 600

# define KEY_W      119
# define KEY_S      115
# define KEY_A      97
# define KEY_D      100
# define KEY_M      109
# define KEY_H      104
# define KEY_E      101
# define KEY_LEFT   65361
# define KEY_RIGHT  65363
# define KEY_ESC    65307
# define KEY_SPACE   32

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.02

# define MINIMAP_RADIUS 5
# define MINIMAP_SCALE 12
# define MINIMAP_WIDTH 66
# define MINIMAP_HEIGHT 66

# define MAX_DOORS 64

# include "types.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include "string_utils.h"
# include "enemy.h"
# include "movement_utils.h"

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	dir;
}	t_player;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
}	t_texture;

typedef struct s_door_timer
{
	int		x;
	int		y;
	double	open_time;
}	t_door_timer;

typedef struct s_enemy
{
	double		x;
	double		y;
	t_texture	texture;
	bool		can_move;
}	t_enemy;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*floor_texture;
	char		*ceiling_texture;
	int			floor_from_texture;
	int			ceiling_from_texture;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	floor_tex;
	t_texture	ceiling_tex;
	t_texture	door;
	t_texture	game_over;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_height;
	int			map_width;
}	t_config;

typedef struct s_stripe_context
{
	int				stripe;
	double			step;
	double			tex_pos;
	t_enemy_bounds	*b;
	t_enemy			*e;
	t_game			*g;
}	t_stripe_context;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_enemy_bounds
{
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		real_start_x;
	int		draw_start_x;
	int		draw_end_x;
	double	tx;
	double	ty;
	double	tx_camera;
}	t_enemy_bounds;

typedef struct s_game
{
	int				minimap_enabled;
	void			*mlx;
	void			*win;
	t_img			frame;
	t_config		config;
	t_player		player;
	t_keys			keys;
	t_img			weapon;
	int				look_offset;
	int				health;
	int				frame_count;
	int				lives;
	int				game_over;
	t_door_timer	door_timers[MAX_DOORS];
	int				num_open_doors;
	t_enemy			enemies[64];
	int				num_enemies;
	double			z_buffer[WIDTH];
	int				is_jumping;
	double			jump_time;
	double			camera_height;
}	t_game;

/* Game */
int		exit_error(char *msg);
void	init_game(t_game *game, char *map_file);
void	start_game(t_game *game);
void	clean_exit(t_game *game, int exit_code);

/* Render */
void	render_walls(t_game *game);
void	draw_minimap(t_game *game);
void	draw_minimap_tile(t_game *game, int x, int y, int color);
void	draw_crosshair(t_game *game);
void	draw_health_bar(t_game *game);
void	draw_game_over_screen(t_game *game);
void	draw_heart(t_game *game, int x, int y, int filled);
void	render_enemies(t_game *game);
void	update_enemies(t_game *game);
int		is_door(char tile);
int		is_closed_door(char tile);
int		is_open_door(char tile);
bool	has_line_of_sight(t_game *g, double ex, double ey);
int		is_walkable(t_game *game, double x, double y);

/* Init */
void	init_mlx(t_game *game);
void	init_frame_buffer(t_game *game);
void	load_environment_textures(t_game *game);
void	load_weapon(t_game *game);
void	finalize_map_dimensions(t_config *config);

/* Input */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		handle_movement(t_game *game);
int		mouse_move(int x, int y, t_game *game);
int		render_frame(void *param);
int		is_walkable_tile(char tile);
void	handle_jump(t_game *g);
void	set_pixel(t_img *img, int x, int y, int color);
void	load_enemy_textures(t_game *game);

/* Utils */
int		map_height(t_game *game);
int		ends_with(const char *str, const char *suffix);
void	rotate_player(t_game *g, double rot);

#endif
