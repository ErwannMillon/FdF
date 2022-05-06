SRCS := fdf.c draw_utils.c draw_functions2.c array_utils2.c array_utils.c win_utils.c hooks.c map_parse.c movement_operations.c free_functions.c matrix_operations.c draw_functions.c 
NAME = fdf
CFLAGS = -Wall -Wextra -Werror
HEADERS = libft.h ft_printf.h get_next_line.h fdf.h
INCLUDEDIR = ./headers
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
ASAN = -fsanitize=address -g
OBJS := $(SRCS:%.c=%.o)
OPTIFLAGS = -Ofast -ffast-math
#ADD CFLAGS!!!

%.o: %.c
	gcc $(CFLAGS) -Imlx -I$(INCLUDEDIR) $(ASAN) -c $< -o $@
all: $(NAME)
$(NAME): libft.a $(OBJS)
	gcc $(OBJS) -lm $(MLXFLAGS) $(ASAN) -o $(NAME) libft.a
libft.a:
	$(MAKE) -C ./libftextended
	cp libftextended/libft.a ./
test: $(NAME)
	gcc -ggdb main.c $(SRCS) -Werror -Wextra -Wall libft.a
asan: $(OBJS)
	gcc -fsanitize=address $(OBJS) -o $(NAME)
git:
	git add ./libftextended $(SRCS) Makefile $(INCLUDEDIR)
clean:
	$(MAKE) -C ./libftextended clean
	rm -f $(OBJS)
fclean: clean
	$(MAKE) -C ./libftextended fclean
	rm -f $(NAME)
re: fclean $(NAME)

.PHONY:	all clean fclean re 
