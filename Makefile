NAME	:= miniRT

CFLAGS	:= -Wextra -Wall -Werror

LIBMLX	:= ./MLX42

LIBLIBFT	:= ./libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBLIBFT)

LIBS	:= $(LIBMLX)/build/libmlx42.a -L$(LIBLIBFT) -lft -ldl -lglfw -pthread -lm

SRCS = src/main.c \
src/setup_scene_description/setup_scene_checks.c \
src/setup_scene_description/setup_scene_description.c \
src/error_exit.c \
src/basic_utils.c \
src/setup_scene_description/set_elements_declared_once.c \
src/setup_scene_description/setup_scene_utils.c \
src/setup_scene_description/set_element_arguments.c \
src/setup_scene_description/set_element_arguments_2.c \
src/setup_scene_description/set_elements_objects.c \
src/malloc_tracker/malloc_tracked.c \
src/malloc_tracker/free_tracked.c \
src/setup_scene_description/object_nodes.c \
src/raytracing/raytracing.c \
src/raytracing/vector_math.c \
src/raytracing/vector_math2.c \
src/raytracing/intersection/intersect.c \
src/raytracing/intersection/intersect_plane.c \
src/raytracing/intersection/intersect_sphere.c \
src/raytracing/intersection/intersect_cylinder.c \
src/raytracing/intersection/math_formulas.c \
src/raytracing/intersection/intersect_utils.c \
src/DEL_utils.c \
src/lights/light_tracing.c \
src/lights/color_math.c \
src/lights/color_math2.c \


OBJS	:= ${SRCS:.c=.o}

RM = rm -rf

all: libft libmlx $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "MLX42 not found, cloning..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C $(LIBLIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) $< -c -o $@ $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -lm $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(NAME) compiled successfully.\n"

clean:
	$(RM) $(OBJS)
	@$(RM) $(LIBMLX)/build
	@$(MAKE) clean -C $(LIBLIBFT)

fclean: clean
	$(RM) $(NAME)
	@$(RM) $(LIBMLX)
	@$(MAKE) fclean -C $(LIBLIBFT)

re: fclean all

.PHONY: all clean fclean re libmlx libft
