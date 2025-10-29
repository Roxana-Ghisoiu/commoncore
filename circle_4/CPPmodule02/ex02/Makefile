# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 12:55:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/09 10:53:32 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := a.out
CPP        := c++
CFLAGS    := -Wall -Wextra -Werror -std=c++98
RM          := rm -f

SRCS        := main.cpp Fixed.cpp
OBJS        := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) -o $(NAME) $(OBJS)


clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re