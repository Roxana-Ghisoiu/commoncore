# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 14:10:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/09 11:29:08 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 14:10:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/09 12:44:43 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := bsp
TEST    := bsp_test

CPP     := c++
CFLAGS  := -Wall -Wextra -Werror -std=c++98
RM      := rm -f

# --- Exercitiul principal ---
SRCS    := main.cpp Fixed.cpp Point.cpp bsp.cpp
OBJS    := main.o Fixed.o Point.o bsp.o

# --- Test separat (nu afecteaza executabilul principal) ---
TEST_SRCS := test_main.cpp Fixed.cpp Point.cpp bsp.cpp
TEST_OBJS := test_main.o Fixed.o Point.o bsp.o

# Implicit: construieste exercitiul
all: $(NAME)

# Link principal
$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) -o $(NAME) $(OBJS)

# Link test
$(TEST): $(TEST_OBJS)
	$(CPP) $(CFLAGS) -o $(TEST) $(TEST_OBJS)

# Regula generica de compilare .cpp -> .o
%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

# Ruleaza: make test  (construieste doar binarul de test)
test: $(TEST)

# Optional: ruleaza testul dupa build
run_test: $(TEST)
	./$(TEST)

clean:
	@$(RM) $(OBJS) $(TEST_OBJS)

fclean: clean
	@$(RM) $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test run_test
