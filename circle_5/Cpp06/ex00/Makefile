# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

NAME      := a.out
CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -std=c++98 -I inc

SRCS      := src/main.cpp \
             src/ScalarConverter.cpp

OBJS      := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp inc/ScalarConverter.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re