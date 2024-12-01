NAME = cub3D_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

# FRAM = -framework Cocoa -framework OpenGL -framework IOKit

GLFW_PATH = /Users/hben-laz/.brew/lib # Update to your GLFW location
LDFLAGS = -lglfw
LIBS = -L$(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOKit

ft = 	main.c get_next_line.c ft_strcmp.c get_texture.c get_texture_helper.c \
		get_map.c add_spaces.c actions.c pars_map.c draw.c get_intercept.c \
		ray_casting.c mini_map.c texture.c player.c

libft = libft/ft_isalnum.c libft/ft_itoa.c libft/ft_memset.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_tolower.c \
		libft/ft_isalpha.c libft/ft_memchr.c libft/ft_putchar_fd.c libft/ft_strchr.c libft/ft_strlcat.c libft/ft_strnstr.c libft/ft_toupper.c \
		libft/ft_atoi.c libft/ft_isascii.c libft/ft_memcmp.c libft/ft_putendl_fd.c libft/ft_strdup.c libft/ft_strlcpy.c libft/ft_strrchr.c \
		libft/ft_bzero.c libft/ft_isdigit.c libft/ft_memcpy.c libft/ft_putnbr_fd.c libft/ft_striteri.c libft/ft_strlen.c libft/ft_strtrim.c \
		libft/ft_calloc.c libft/ft_isprint.c libft/ft_memmove.c libft/ft_putstr_fd.c libft/ft_strmapi.c libft/ft_substr.c

SRC = $(libft) $(ft)

OBJ = $(SRC:.c=.o)

# Paths for MLX42
MLX_PATH = ../../mlx
MLX_BUILD = $(MLX_PATH)/build
MLX_INCLUDE = $(MLX_PATH)/include

all: $(NAME)

$(NAME): $(OBJ) cub3D_bonus
	$(CC) $(CFLAGS) $(OBJ) -I$(MLX_INCLUDE) -L$(MLX_BUILD) -lmlx42 $(LDFLAGS) $(LIBS) -o $(NAME)

%.o: %.c cub3D_bonus
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all