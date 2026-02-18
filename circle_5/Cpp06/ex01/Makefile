NAME = serialize

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

INC = -I inc

SRC = src/main.cpp src/Serializer.cpp
OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re