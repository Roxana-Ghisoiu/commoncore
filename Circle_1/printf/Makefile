NAME = libftprintf.a
LIBFTNAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFTDIR = ./libft

LIBFT_SRCS = ft_atoi.c \
             ft_bzero.c \
             ft_calloc.c \
             ft_isalnum.c \
             ft_isalpha.c \
             ft_isascii.c \
             ft_isdigit.c \
             ft_isprint.c \
             ft_itoa.c \
             ft_memchr.c \
             ft_memcmp.c \
             ft_memcpy.c \
             ft_memmove.c \
             ft_memset.c \
             ft_putchar_fd.c \
             ft_putendl_fd.c \
             ft_putnbr_fd.c \
             ft_putstr_fd.c \
             ft_split.c \
             ft_strchr.c \
             ft_strdup.c \
             ft_striteri.c \
             ft_strjoin.c \
             ft_strlcat.c \
             ft_strlcpy.c \
             ft_strlen.c \
             ft_strmapi.c \
             ft_strncmp.c \
             ft_strnstr.c \
             ft_strrchr.c \
             ft_strtrim.c \
             ft_substr.c \
             ft_tolower.c \
             ft_toupper.c

BONUS_SRCS = ft_lstnew_bonus.c \
             ft_lstadd_front_bonus.c \
             ft_lstsize_bonus.c \
             ft_lstlast_bonus.c \
             ft_lstadd_back_bonus.c \
             ft_lstdelone_bonus.c \
             ft_lstclear_bonus.c \
             ft_lstiter_bonus.c \
             ft_lstmap_bonus.c

SRCS = ft_printf.c \
       ft_print_ptr.c \
       ft_print_str.c \
       ft_print_num_unsigned.c \
       ft_print_num.c \
       ft_print_num_base.c \
       ft_print_char.c

SRCS += $(addprefix $(LIBFTDIR)/, $(LIBFT_SRCS)) \
        $(addprefix $(LIBFTDIR)/, $(BONUS_SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

makelibft:
	@make -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFTNAME) .
	@mv $(LIBFTNAME) $(NAME)

$(NAME): makelibft $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFTDIR) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@cd $(LIBFTDIR) && make clean
    
fclean: clean
	@$(RM) $(NAME)
	@cd $(LIBFTDIR) && make fclean
    
re: fclean all

.PHONY: all clean fclean re
