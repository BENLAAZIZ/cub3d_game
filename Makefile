NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror# -g -fsanitize=address
# CFLAGS += -Ofast
RM = rm -f

SRC= main.c libft/ft_strjoin.c libft/ft_strlen.c get_next_line_utils.c \
	get_next_line.c libft/ft_strcmp.c libft/ft_strncmp.c actions.c \
 	libft/ft_split.c list_fun.c libft/ft_atoi.c libft/ft_strrchr.c \
	libft/ft_strtrim.c libft/ft_strchr.c raycaster.c   draw.c intersiction.c \
	texture.c

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