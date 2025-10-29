# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 16:45:00 by rghisoiu          #+#    #+#              #
#    Updated: 2025/09/05 14:46:24 by rghisoiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME    := a.out

# Dirs
SRCDIR  := src
INCDIR  := inc
OBJDIR  := obj

# Compiler & flags
CXX     := c++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98
CPPFLAGS:= -MMD -MP -I$(INCDIR)

# Sources (all .cpp in src/)
SRCS    := $(wildcard $(SRCDIR)/*.cpp)

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

# Include auto-generated dependencies
-include $(DEPS)

.PHONY: all clean fclean re