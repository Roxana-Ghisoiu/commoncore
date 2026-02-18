NAME        := intern
CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98 -Iinc
SRCDIR      := src
INCDIR      := inc

SRC := $(SRCDIR)/Bureaucrat.cpp $(SRCDIR)/AForm.cpp \
       $(SRCDIR)/ShrubberyCreationForm.cpp \
       $(SRCDIR)/RobotomyRequestForm.cpp \
       $(SRCDIR)/PresidentialPardonForm.cpp \
       $(SRCDIR)/Intern.cpp \
       $(SRCDIR)/main.cpp

OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(INCDIR)/Bureaucrat.hpp $(INCDIR)/AForm.hpp \
            $(INCDIR)/ShrubberyCreationForm.hpp \
            $(INCDIR)/RobotomyRequestForm.hpp \
            $(INCDIR)/PresidentialPardonForm.hpp \
            $(INCDIR)/Intern.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re