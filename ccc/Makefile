NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

RM = rm -f

SRC= main.c ft_strjoin.c ft_strlen.c get_next_line_utils.c get_next_line.c ft_strcmp.c ft_strncmp.c ft_split.c \
	list_fun.c ft_atoi.c raycaster.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cub3d.h
		 $(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all