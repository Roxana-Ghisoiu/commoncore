# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 13:55:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/09 12:22:06 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binarul principal (exercitiul)
NAME    := claptrap
# Binarul de test
TEST    := claptrap_test

CPP     := c++
CFLAGS  := -Wall -Wextra -Werror -std=c++98
RM      := rm -f

SRCS    := main.cpp ClapTrap.cpp
OBJS    := $(SRCS:.cpp=.o)

# Surse test (NU includ main.cpp)
TEST_SRCS := test_main.cpp ClapTrap.cpp
TEST_OBJS := $(TEST_SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) -o $(NAME) $(OBJS)

$(TEST): $(TEST_OBJS)
	$(CPP) $(CFLAGS) -o $(TEST) $(TEST_OBJS)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

test: $(TEST)

run_test: $(TEST)
	./$(TEST)

clean:
	@$(RM) $(OBJS) $(TEST_OBJS)

fclean: clean
	@$(RM) $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test run_test
