NAME = cub3d

SRC = add_colors.c\
	add_wall.c\
	ft_split.c\
	ft_split2.c\
	main.c\
	utils.c\
	./parsing/get_next_line.c\
	./parsing/get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

all: {$NAME}

${NAME}: ${OBJ}
	cc -Wall -Werror -Wextra ${OBJ} -o $@

%.o: %.c cub3d.h
	cc -Wall -Werror -Wextra -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}
