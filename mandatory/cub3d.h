/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:16:53 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/06 18:12:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# include "../../mlx/include/MLX42/MLX42.h"
# include <math.h>
# include <limits.h>

# define BUFFER_SIZE 10
# define SCREEN_W 2000
# define SCREEN_H 1000
# define T_S 50.0
# define NUM_RAYS SCREEN_W

typedef enum e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}	t_type;

typedef struct s_texture
{
	char				*path;
	int					identifier;
	int					color_floor;
	int					color_ceiling;
	struct s_texture	*next;
}	t_texture;

typedef struct s_image
{
	void			*image;
	mlx_texture_t	*texture;
}	t_image;

typedef struct s_data
{
	t_image			image[4];
	t_image			*imgx;
	t_texture		*tex;
	mlx_image_t		*img;
	char			**all_map;
	void			*mlx;
	int				height;
	int				lenght;
	double			angle;
	double			p_x;
	double			p_y;
	int				ceiling_color;
	int				floor_color;
	double			speed;
	double			fov;
}	t_data;

typedef struct s_player
{
	double	ray_y;
	double	ray_x;
	double	step_x;
	double	step_y;
	double	ray_step;
	int		z;
}	t_player;

typedef struct s_ray
{
	double	rayangle;
	double	v_distance;
	double	h_distance;
	double	h_hit_x;
	double	h_hit_y;
	double	v_hit_x;
	double	v_hit_y;
	double	x_hit;
	double	y_hit;
	double	distance;
	int		lookingdown;
	int		lookingup;
	int		lookingright;
	int		lookingleft;
	int		flag;
}	t_ray;

typedef struct s_var
{
	double			xintercept;
	double			yintercept;
	double			xtocheck;
	double			ytocheck;
	double			distance;
	double			ystep;
	double			xstep;
	double			line_height;
	double			top_y;
	double			bottom_y;
	int				color;
	int				ofsset_x;
	int				offset_y;
	unsigned int	*pixel;
}	t_var;

//libft
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_isprint(int c);
int			ft_atoi(char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_tolower(int c);
int			ft_isprint(int c);
int			ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
int			ft_toupper(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
void		ft_putchar_fd(char c, int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t num_elements, size_t element_size);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putnbr_fd(int n, int fd);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
//libft

//get_next_line
char		*get_next_line(int fd);
//get_next_line

//get_texture
void		*check_rgp(char *str, int r, int g, int *color);
t_texture	*get_texture(int fd, t_texture *tex, int i, int count);
t_texture	*ft_lstnew(t_texture *new, char *line, int i);
void		lstadd_back(t_texture **lst, t_texture *new);
//get_texture

//get_map
char		**get_map(int fd, char *line, char *rest, char **map);
//get_map

//pars_map
char		**pars_map(char *argv, t_texture **textures, char **map);
char		**add_spaces(char **map, int i, int j);
//pars_map

int			is_wall(t_data *data, double y, double x);

//actions
void		move_player_down(t_data *data);
void		move_player_up(t_data *data);
void		move_player_left(t_data *data);
void		move_player_right(t_data *data);
void		player_rot(t_data *data);
//actions

//draw
int			draw_wall(t_data *data, t_ray *ray, int column);
void		draw_floor_ceiling(t_data *data, double distance, double column);
//draw

//get_intercept
double		get_v_intercept(t_data *data, t_ray *ray);
double		get_h_intercept(t_data *data, t_ray *ray);
//get_intercept

//ray_casting

void		init_ray(t_ray *ray);
int			cast_rays(t_data *data);
//ray_casting

//main
int			point_image_texture(t_data *data, t_ray *ray);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int			get_image_texture(t_data *data, t_texture *tex, int i);
void		lst_clear(t_texture **lst);
void		free_double(char **map);
void		get_player_position(t_data *data);
int			check_image_texture(t_data *data, t_texture *tex, int i);
//main
#endif