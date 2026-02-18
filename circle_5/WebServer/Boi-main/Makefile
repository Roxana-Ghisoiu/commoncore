NAME := webserver
CC := c++
FLAGS := -std=c++98 -fsanitize=address
INCLUDES := -I include

SRC_DIRS := src src/core src/http src/cgi src/config src/session src/utils

SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

OBJ := $(SRC:src/%.cpp=objects/%.o)

OBJECTS_DIRS := objects objects/core objects/http objects/cgi objects/config objects/session objects/utils

all: $(NAME)

$(OBJECTS_DIRS):
	@mkdir -p $(OBJECTS_DIRS)

objects/%.o: src/%.cpp | $(OBJECTS_DIRS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME)

clean:
	$(RM) -rf objects

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re