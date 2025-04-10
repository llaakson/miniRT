# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 13:23:22 by aalbrech          #+#    #+#              #
#    Updated: 2025/04/10 17:47:20 by aalbrech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
src/setup_scene_description/initial_checks.c \
src/setup_scene_description/setup_scene_description.c \
src/error_exit.c \
src/basic_utils.c \
src/setup_scene_description/set_elements.c \


OBJ = $(SRC:.c=.o)

NAME = miniRT

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

.PHONY = all clean fclean re

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all