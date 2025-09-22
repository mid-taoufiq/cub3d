NAME = cub3d

SRC = main.c\
	garbage.c\
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

all: ${NAME}

${NAME}: ${OBJ}
	cc -Wall -Werror -Wextra -g ${OBJ} -o $@

%.o: %.c cub3d.h
	cc -Wall -Werror -Wextra -g -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}
