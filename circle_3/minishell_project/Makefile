NAME = minishell

# Directories
SRC_DIR := src
INC_DIR := inc
LIBFT_DIR := libft
BUILD_DIR := obj

# Local readline path
READLINE_PATH := $(HOME)/.local/pkg/readline

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR) -I$(READLINE_PATH)/include -I$(LIBFT_DIR)
LDFLAGS := -L$(READLINE_PATH)/lib -lreadline -L$(LIBFT_DIR) -lft

# Sources and objects
SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Create obj subdirs automatically
DIRS := $(sort $(dir $(OBJ_FILES)))
$(shell mkdir -p $(DIRS))

# Default rule
all: $(LIBFT_DIR)/libft.a $(NAME)

# Link the final executable
$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(NAME)
	@echo "\033[1;32mminishell was successfully created!\033[0m"

# Compile source files into object files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Libft if needed
$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

# Clean object files
clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(BUILD_DIR)

# Clean everything
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Rebuild all
re: fclean all

.PHONY: all clean fclean re

