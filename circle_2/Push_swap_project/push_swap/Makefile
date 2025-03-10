# Name of the executable
NAME = push_swap

# Compiler and compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directories for source files and object files
SRC_DIR = src
OBJ_DIR = obj
INCLUDES = -Iincludes -Ilibft

# List of source files
SRC_FILES = main.c parse_args.c push_swap.c stack.c stack_utils.c operations.c \
            rotate.c reverse_rotate.c sort_small.c sort_radix.c ft_atol.c checker.c error_free.c

# Add the source directory path to each source file
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Create a list of object files from source files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Path to the Libft library
LIBFT = libft/libft.a

# Default rule: Compile the project
all: $(NAME)

# Rule to build the executable
$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@echo "Compiling push_swap..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Rule to compile each .c file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile the Libft library before push_swap
$(LIBFT):
	@echo "Compiling libft..."
	@make -C libft

# Remove all object files
clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

# Remove object files and the executable
fclean: clean
	rm -f $(NAME)
	make fclean -C libft

# Recompile everything from scratch
re: fclean all

# Mark these targets as not being actual files
.PHONY: all clean fclean re
