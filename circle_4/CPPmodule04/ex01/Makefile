# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 14:50:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/05 13:32:27 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME    := brainAnimal

# Dirs
SRCDIR  := src
INCDIR  := inc
OBJDIR  := obj

# Compiler & flags
CXX     := c++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98
CPPFLAGS:= -MMD -MP -I$(INCDIR)

# Sources (explicit list; adaugă aici dacă mai ai .cpp-uri)
SRCS    := $(SRCDIR)/main.cpp \
           $(SRCDIR)/Animal.cpp \
           $(SRCDIR)/Dog.cpp \
           $(SRCDIR)/Cat.cpp \
		   $(SRCDIR)/WrongCat.cpp \
		   $(SRCDIR)/WrongAnimal.cpp \
           $(SRCDIR)/Brain.cpp

# Objects & deps
OBJS    := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS    := $(OBJS:.o=.d)

# Default
all: $(NAME)

# Link
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Ensure obj/ exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean
clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Include auto-generated deps
-include $(DEPS)

.PHONY: all clean fclean re