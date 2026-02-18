# Simple Makefile for cpp08/ex00 - Easy find
# Builds a single executable named 'easyfind' from main.cpp

NAME     := easyfind
CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)
HEADERS := easyfind.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re