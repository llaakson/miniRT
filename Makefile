NAME	:= miniRT

CFLAGS	:= -Wextra -Wall -Werror

LIBMLX	:= ./MLX42

LIBLIBFT	:= ./libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBLIBFT)

LIBS	:= $(LIBMLX)/build/libmlx42.a -L$(LIBLIBFT) -lft -ldl -lglfw -pthread -lm

SRCS	:= ./src/main.c \

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
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
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
