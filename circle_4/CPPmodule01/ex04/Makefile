NAME     := sed_is_for_losers
CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
RM       := rm -f

SRCS := \
	main.cpp \
	Sed.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp Sed.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
