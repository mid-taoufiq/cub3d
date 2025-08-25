NAME = cub3d

SRC = main.c\
	garbage.c\
	./parsing/add_colors.c\
	./parsing/parse_map.c\
	./parsing/add_wall.c\
	./parsing/ft_split.c\
	./parsing/ft_split2.c\
	./parsing/utils.c\
	./parsing/utils2.c\
	./parsing/gnl/get_next_line.c\
	./parsing/gnl/get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	cc -Wall -Werror -Wextra -fsanitize=address -g ${OBJ} -o $@

%.o: %.c cub3d.h
	cc -Wall -Werror -Wextra -fsanitize=address -g -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}
