NAME = cub3D

FLAGS = -Wall #-Werror -Wextra

SRC = main.c\
	garbage.c\
	draw.c\
	recasting.c\
	player.c\
	movement.c\
	./parsing/parsing.c\
	./parsing/add_colors.c\
	./parsing/add_to_map.c\
	./parsing/parse_map.c\
	./parsing/add_wall.c\
	./parsing/ft_split.c\
	./parsing/utils.c\
	./parsing/utils2.c\
	./parsing/utils3.c\
	./parsing/get_next_line.c\

OBJ = $(SRC:.c=.o)

LIB_MLX = libmlx42.a

MLX_FLAG = -L/mnt/homes/tibarike/homebrew/opt/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: ${NAME}

${NAME}: ${OBJ} ${LIB_MLX}
	cc ${FLAGS} ${MLX_FLAG} -fsanitize=address -g ${OBJ} ${LIB_MLX} -o $@

%.o: %.c cub3d.h
	cc ${FLAGS} -fsanitize=address -g -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}
