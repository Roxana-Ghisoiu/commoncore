# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 13:51:09 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/01 12:28:50 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phonebook
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp Contact.cpp PhoneBook.cpp
OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)
