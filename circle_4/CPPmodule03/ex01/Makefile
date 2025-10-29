# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 13:55:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/09 12:57:56 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main program
NAME      := ScavTrap
# Test program
TEST      := scav_test

CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -std=c++98
RM        := rm -f

# Source files for the main program (do not use wildcard)
SRCS      := main.cpp ClapTrap.cpp ScavTrap.cpp
OBJS      := $(SRCS:.cpp=.o)

# Source files for the test program (exclude main.cpp of the exercise)
TEST_SRCS := test_main.cpp ClapTrap.cpp ScavTrap.cpp
TEST_OBJS := $(TEST_SRCS:.cpp=.o)

# Default rule: build the main program
all: $(NAME)

# Link the main program
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Link the test program
$(TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build only the test program
test: $(TEST)

# Run the test program
run_test: $(TEST)
	./$(TEST)

# Clean object files
clean:
	@$(RM) $(OBJS) $(TEST_OBJS)

# Clean everything
fclean: clean
	@$(RM) $(NAME) $(TEST)

# Rebuild from scratch
re: fclean all

.PHONY: all clean fclean re test run_test