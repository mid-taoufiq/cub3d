NAME = cub3d

SRC = main.c\
	garbage.c\
	./Parsing/parsing.c\
	./Parsing/add_colors.c\
	./Parsing/add_to_map.c\
	./Parsing/parse_map.c\
	./Parsing/add_wall.c\
	./Parsing/ft_split.c\
	./Parsing/utils.c\
	./Parsing/utils2.c\
	./Parsing/utils3.c\
	./Parsing/get_next_line.c\

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
