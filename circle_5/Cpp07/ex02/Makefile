NAME      = a.out
SRCS      = main.cpp
OBJS      = $(SRCS:.cpp=.o)

CXX       = c++
CXXFLAGS  = -Wall -Wextra -Werror -std=c++98
RM        = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

main.o: main.cpp Array.hpp Array.tpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re