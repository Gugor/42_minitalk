# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 16:24:04 by hmontoya          #+#    #+#              #
#    Updated: 2023/09/21 17:00:06 by hmontoya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================== Color Format =====================================#
BLACK 		= "\033[1;30m"
RED 		= "\033[1;31m"
GREEN 		= "\033[1;32m"
YELLOW 		= "\033[1;33m"
BLUE 		= "\033[1;34m"
MAGENTA		= "\033[1;35m"
CYAN		= "\033[1;36m"
WHITE 		= "\033[1;37m"
RESET 		= "\033[1;0m"

# Nombre del ejecutable
SERVER_EXEC = server
CLIENT_EXEC = client

# Rutas a directorios
SRC_DIR 	= src
INC_DIR 	= includes
LIBFT_DIR 	= libft
PRINTF_DIR 	= ft_printf

# Lista de archivos fuente
SERV_SRC_FILES 	= server.c
CLIE_SRC_FILES 	= client.c

# Lista de archivos de encabezado
INC_FILES 	= mintalk.h ft_printf.h libft.h

# Rutas completas a archivos fuente y de encabezado
SERV_SRCS 	= $(addprefix $(SRC_DIR)/, $(SERV_SRC_FILES))
CLIE_SRCS 	= $(addprefix $(SRC_DIR)/, $(CLIE_SRC_FILES))
INCS 		= $(addprefix $(INC_DIR)/, $(INC_FILES))
OBJS 		= $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

# Compilador y opciones de compilación
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR)

# Bibliotecas
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Regla principal
all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERV_SRCS) $(LIBFT) $(PRINTF)
	@echo $(BLUE)
	$(CC) $(CFLAGS) -o $@ $(SERV_SRCS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf
	@echo $(RESET)

$(CLIENT_EXEC): $(CLIE_SRCS) $(LIBFT) $(PRINTF)
	@echo $(BLUE)
	$(CC) $(CFLAGS) -o $@ $(CLIE_SRCS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf
	@echo $(RESET)

# Reglas para construir las bibliotecas
$(LIBFT):
	@echo $(GREEN)
	$(MAKE) -C $(LIBFT_DIR) 
	@echo $(RESET)

$(PRINTF):
	@echo $(GREEN)
	$(MAKE) -C $(PRINTF_DIR)
	@echo $(RESET)

# Limpieza
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	@rm -vf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	@rm -vf $(SERVER_EXEC) $(CLIENT_EXEC)

re: fclean all

.PHONY: all clean fclean re
