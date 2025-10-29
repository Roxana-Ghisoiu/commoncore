# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 14:26:46 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/01 14:26:53 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = zombie

CXX     = c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98

SRCS    = main.cpp Zombie.cpp newZombie.cpp randomChump.cpp
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
