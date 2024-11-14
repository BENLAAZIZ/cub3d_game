/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:06:34 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/14 16:56:54 by hben-laz         ###   ########.fr       */
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


#define FOV (60 * (M_PI / 180))
# define RAD(X) (X * (M_PI / (float)180))
# define DEGREE(X) ((X * 360) / 2 * M_PI)
#define NUM_RAYS 60

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
	char			*Path;
	char			*rgp_color;
	int				identifier;
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

typedef struct s_data
{
	
	char	**all_map;
	void	*mlx;
	void	*win;
	void	*win_test;
	int		height;
	int		lenght;
	double	angle;
	double		p_x;
	double		p_y;
	
	// *****************
	float turnDirection;
	int walkDirection;
	float radius;
	float rotationAngle;
	float moveSpeed;
	float rotationSpeed;
	// void *img;
	t_image image[4];
	// *****************
	t_texture *tex;
	
}t_data;

typedef struct s_ray {

	double rayAngle;
	double v_distance;
    double h_distance;
	double h_hit_x;
    double h_hit_y;
    double v_hit_x;
    double v_hit_y;

	double x_hit;
	double y_hit;
	double distance;
	int lookingDown;
	int lookingUp;
	int lookingRight;
	int lookingLeft;
	int flag;
	struct s_ray *next;
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

//libft
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
float	normalize_angle(float angle);
void draw_wall(t_data *data, t_ray *ray, int column);
void draw_floor(t_data *data, double distance, double column);
// int is_wall(t_data *data, double y, double x);

#endif