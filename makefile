NAME = cub3d

FLAGS = -Wall #-Werror -Wextra

SRC = main.c\
	garbage.c\
	./parsing/add_colors.c\
	./parsing/add_wall.c\
	./parsing/ft_split.c\
	./parsing/ft_split2.c\
	./parsing/utils.c\
	./parsing/utils2.c\
	./parsing/get_next_line.c\
	./parsing/get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

LIB_MLX = libmlx42.a

MLX_FLAG = -lglfw -framework Cocoa -framework OpenGL -framework IOKit

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
