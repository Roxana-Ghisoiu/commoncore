# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 13:55:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/09 13:23:12 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main program
NAME       := FragTrap
# Test program
TEST       := frag_test

CXX        := c++
CXXFLAGS   := -Wall -Wextra -Werror -std=c++98
RM         := rm -f

# Sources for the main program (no wildcard)
SRCS       := main.cpp ClapTrap.cpp FragTrap.cpp
OBJS       := $(SRCS:.cpp=.o)

# Sources for the test program (exclude main.cpp of the exercise)
TEST_SRCS  := test_main.cpp ClapTrap.cpp FragTrap.cpp
TEST_OBJS  := $(TEST_SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST)

run_test: $(TEST)
	./$(TEST)

clean:
	@$(RM) $(OBJS) $(TEST_OBJS)

fclean: clean
	@$(RM) $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test run_test
