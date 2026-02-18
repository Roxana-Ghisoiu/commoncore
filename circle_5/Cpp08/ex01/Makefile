# ex01 - Span
NAME     := ex01
CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp Span.cpp
OBJS := $(SRCS:.cpp=.o)
HEADERS := Span.hpp

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