# Numele executabilelor
NAME_CLIENT = client
NAME_SERVER = server

# Directorul și biblioteca LibftPrintf
LIBFTPRINTF_DIR = LibftPrintf
LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a

# Fișierele sursă pentru server și client
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Include directoarele
INCLUDES = -I$(LIBFTPRINTF_DIR) -I.

# Compilatorul și opțiunile de compilare
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

# Reguli principale
all: $(LIBFTPRINTF) $(NAME_SERVER) $(NAME_CLIENT)

# Crează serverul
$(NAME_SERVER): $(SERVER_SRC) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(SERVER_SRC) $(LIBFTPRINTF) -o $(NAME_SERVER)

# Crează clientul
$(NAME_CLIENT): $(CLIENT_SRC) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(LIBFTPRINTF) -o $(NAME_CLIENT)

# Construiește biblioteca libftprintf.a
$(LIBFTPRINTF):
	$(MAKE) -C $(LIBFTPRINTF_DIR)

# Curățare
clean:
	$(MAKE) -C $(LIBFTPRINTF_DIR) clean
	rm -f $(SERVER_SRC:.c=.o) $(CLIENT_SRC:.c=.o)

# Curățare completă
fclean: clean
	$(MAKE) -C $(LIBFTPRINTF_DIR) fclean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

# Reconstruiește tot
re: fclean all

.PHONY: all clean fclean re
