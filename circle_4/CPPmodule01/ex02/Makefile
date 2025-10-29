# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 17:25:30 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/01 17:26:21 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = brain

CXX     = c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98

SRCS    = main.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
