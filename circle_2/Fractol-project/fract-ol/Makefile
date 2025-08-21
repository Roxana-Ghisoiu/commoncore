NAME = fractol

# Directories
SRC_DIR = srcs
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = include/LibftPrintf
MLX_DIR = include/minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

# Source files
SRC_FILES = event.c \
            fractal_bonus.c \
            fractol.c \
            julia.c \
            main.c \
            mandelbrot.c \
            mouse_and_keys.c \
            start_fractal_bonus.c \
            start_fractals.c \
            start_julia.c \
            start_mandelbrot.c \
            utils.c \
            mouse_and_keys_bonus.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-unused-result -g -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

# Libraries
LIBFT = $(LIBFT_DIR)/libftprintf.a
MLX = $(MLX_DIR)/libmlx.a
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Wno-unused-result -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	@if [ ! -f "$@" ]; then $(MAKE) -C $(LIBFT_DIR); fi

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "📥 Downloading MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@echo "⚙️  Compiling MiniLibX..."
	@$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@if [ -d "$(MLX_DIR)" ]; then rm -rf $(MLX_DIR); fi

re: fclean $(MLX) all

.PHONY: all clean fclean re

