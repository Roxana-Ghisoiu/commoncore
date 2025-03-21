# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rghisoiu <rghisoiu@student.42luxembourg>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 15:00:00 by rghisoiu         #+#    #+#              #
#    Updated: 2025/03/20 15:00:00 by rghisoiu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c init_process.c philosopher_routine.c \
			  monitor_philosophers.c open_close_semaphores.c utils.c init_data.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME)
	@echo "Bonus part compiled!"

norm:
	norminette .

.PHONY: all clean fclean re bonus norm
