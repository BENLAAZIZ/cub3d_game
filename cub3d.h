/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:06:34 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/20 00:09:12 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
#define	CUB3D_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mlx.h>
#include <math.h>
#include <limits.h>


#define FOV (60.0 * (M_PI / 180.0))


# define Scren_W 1000 // screen width
# define Scren_H 700 // screen height
# define TILE_SIZE 32 // tile size
#define NUM_RAYS Scren_W

typedef enum e_type {
	NO,
	SO,
	WE,
	EA,
	F,
	C
} t_type;

typedef struct s_texture
{
	char				*Path;
	char				*rgp_color;
	int					identifier;
	struct s_texture	*next;
} t_texture;

typedef struct s_image 
{
	void	*image;
	char	*addr;
	
	int		whith;
	int		height;
	
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_image;

typedef struct s_player 
{
	// double	p_x;
	// double	p_y;
	double	ray_y;
    double	ray_x;
    double	step_x;
    double	step_y;
    double	ray_step;
    int		z;
} t_player;

typedef struct s_data
{
	
	char		**all_map;
	void		*mlx;
	void		*win;
	void		*win_test;
	int			height;
	int			lenght;
	double		angle;
	double		p_x;
	double		p_y;
	t_player	player;
	t_image		image[4];
	
}t_data;

typedef struct s_ray {

	double	rayAngle;
	double	v_distance;
    double	h_distance;
	double	h_hit_x;
    double	h_hit_y;
    double	v_hit_x;
    double	v_hit_y;

	double	x_hit;
	double	y_hit;
	double	distance;
	int		lookingDown;
	int		lookingUp;
	int		lookingRight;
	int		lookingLeft;
	int		flag;
}t_ray;


typedef struct s_mlx
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	char	*f;
	char	*c;
} t_mlx;

#define BUFFER_SIZE 10
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char const *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);


char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
t_texture	*ft_lstnew(t_texture *new, char *line, int i);
void		lstadd_back(t_texture **lst, t_texture *new);
char		*ft_substr(char const *s, unsigned int start, size_t len);
double 		get_v_intercept(t_data *data, t_ray *ray, double xstep, double ystep);
double 		get_h_intercept(t_data *data, t_ray *ray, double xstep, double ystep);
void 		oneRay(t_data *data, t_ray *ray);
void  		castAllRay(t_data *data);
int			key_press(int keycode, t_data *data);
void		get_player_position(t_data *data);
char		*ft_strchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strrchr(const char *s, int c);

//window
int 		create_window(char **map, t_texture *tex);

// action
void	move_player_down(t_data *data);
void	move_player_right(t_data *data);
void	move_player_left(t_data *data);
void	move_player_up(t_data *data);
void    drawmap(t_data *data);
void    drawplayer(t_data *data);
int 	is_wall(t_data *data, double y, double x);
void 	draw_wall(t_data *data, t_ray *ray, int column);
void 	draw_floor(t_data *data, double distance, double column);
int 	get_image_texture(t_data *data, t_texture *tex);
int 	get_addr_texture(t_data *data);
void 	clear_texture(t_texture *tex);
int	mouse_rotate(int x, int y, t_data *data);


#endif