# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 13:23:22 by aalbrech          #+#    #+#              #
#    Updated: 2025/04/23 13:25:41 by aalbrech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
src/setup_scene_description/setup_scene_checks.c \
src/setup_scene_description/setup_scene_description.c \
src/error_exit.c \
src/basic_utils.c \
src/setup_scene_description/set_elements_declared_once.c \
src/setup_scene_description/setup_scene_utils.c \
src/setup_scene_description/set_element_arguments.c \
src/setup_scene_description/set_elements_objects.c \
src/malloc_tracker/malloc_tracker.c \
src/setup_scene_description/object_nodes.c \
src/raytracing/raytracing.c \
src/raytracing/vector_math.c \
src/raytracing/intersection/intersect.c \
src/raytracing/intersection/intersect_plane.c \
src/raytracing/intersection/intersect_sphere.c \
src/raytracing/intersection/intersect_cylinder.c \
src/raytracing/intersection/math_formulas.c \
src/DEL_utils.c


OBJ = $(SRC:.c=.o)

NAME = miniRT

CC = cc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

FLAGS = -lm #for math.h

.PHONY = all clean fclean re

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all