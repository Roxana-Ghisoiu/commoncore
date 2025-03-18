# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 13:00:41 by rghisoiu          #+#    #+#              #
#    Updated: 2025/03/17 19:01:10 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

# Source files
SRCS = main.c philosopher.c arguments.c cleanup.c threads.c utils.c init.c monitor.c

# Object files (generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = philosopher.h

# Rule for compiling the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Rule to compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to remove object files
clean:
	rm -f $(OBJS)

# Rule to remove object files and executable
fclean: clean
	rm -f $(NAME)

# Rule to recompile everything
re: fclean $(NAME)

# Phony targets (these are not actual files)
.PHONY: all clean fclean re
