# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 02:40:00 by vberegoi          #+#    #+#              #
#    Updated: 2025/07/11 02:37:04 by vberegoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iinclude -Iminilibx-linux

MLX		= -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRC_DIR	= src
OBJ_DIR	= obj

SRCS = \
main.c \
$(SRC_DIR)/init/init_game.c \
$(SRC_DIR)/init/init_game_load.c \
$(SRC_DIR)/init/start_game.c \
$(SRC_DIR)/init/clean_exit.c \
$(SRC_DIR)/parse/is_map_line.c \
$(SRC_DIR)/parse/parse_colors.c \
$(SRC_DIR)/parse/parse_line.c \
$(SRC_DIR)/parse/parse_map.c \
$(SRC_DIR)/parse/parse_map_utils.c \
$(SRC_DIR)/parse/parse.c \
$(SRC_DIR)/render/controls.c \
$(SRC_DIR)/render/doors.c \
$(SRC_DIR)/render/doors_utils.c \
$(SRC_DIR)/render/draw_crosshair.c \
$(SRC_DIR)/render/draw_health.c \
$(SRC_DIR)/render/draw_weapon.c \
$(SRC_DIR)/render/jump.c \
$(SRC_DIR)/render/minimap.c \
$(SRC_DIR)/render/minimap_utils.c \
$(SRC_DIR)/render/movement.c \
$(SRC_DIR)/render/movement_utils.c \
$(SRC_DIR)/render/raycast.c \
$(SRC_DIR)/render/raycast_utils.c \
$(SRC_DIR)/render/raycast_utils_norm.c \
$(SRC_DIR)/render/render.c \
$(SRC_DIR)/render/render_background.c \
$(SRC_DIR)/render/render_enemy.c \
$(SRC_DIR)/render/render_enemy_logic.c \
$(SRC_DIR)/render/render_health.c \
$(SRC_DIR)/render/render_text.c \
$(SRC_DIR)/utils/error.c \
$(SRC_DIR)/utils/libft_utils.c \
$(SRC_DIR)/utils/string_utils.c \
$(SRC_DIR)/utils/string_utils_norm.c \
$(SRC_DIR)/utils/texture_utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
