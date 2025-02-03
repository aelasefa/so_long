NAME := so_long

SRC:= get_next_line.c get_next_line_utils.c check_map.c \
	  creat_2d_array.c   map_to_image.c    ft_itoa.c main.c \
	  coin_animation.c enemy_place.c flood_fill.c move_player.c \
	  draw_player_and_exit.c free_map_or_game.c

CC := cc #-g3 -fsanitize=address

CFLAGS := -Wall -Wextra -Werror

LIBXFLAGS := -lmlx -lXext -lX11
#OBJS := $(SRC:.c=.o)
all : $(NAME)

$(NAME) : $(SRC)
	make -C ft_printf/
	$(CC) $(SRC) -g $(LIBXFLAGS) ft_printf/libftprintf.a -o $(NAME)

clean :
	make -C ft_printf fclean
	rm -f $(OBJS)

fclean : clean
	make -C ft_printf fclean
	rm -f $(NAME)

re : fclean all
