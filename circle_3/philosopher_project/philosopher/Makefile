# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 13:00:41 by rghisoiu          #+#    #+#              #
#    Updated: 2025/03/12 13:49:11 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

# Directories
LIBFT_DIR = LibftPrintf
LIBFT = $(LIBFT_DIR)/libftprintf.a

# Source files
SRCS = main.c philosopher.c arguments.c cleanup.c threads.c utils.c init.c

# Object files (generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = philosopher.h

# Rule for compiling the executable (links with LibftPrintf)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Rule to compile LibftPrintf
$(LIBFT):
	make -C $(LIBFT_DIR)

# Rule to compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to remove object files
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

# Rule to remove object files and executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Rule to recompile everything
re: fclean $(NAME)

# Phony targets (these are not actual files)
.PHONY: all clean fclean re