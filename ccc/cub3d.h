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

typedef enum e_type {
	NO,
	SO,
	WE,
	EA,
	F,
	C
} t_type;

typedef struct s_data
{
	
	char	**all_map;
	void	*mlx;
	void	*win;
	void	*win_test;
	int		height;
	int		lenght;
	double	angle;
	int		p_x;
	int		p_y;
	// *****************
	float turnDirection;
	int walkDirection;
	float radius;
	float rotationAngle;
	float moveSpeed;
	float rotationSpeed;
}t_data;

typedef struct s_texture
{
	char			*Path;
	char			*rgp_color;
	int				identifier;
	struct s_texture	*next;
} t_texture;

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
double 		get_h_distance(t_data *data, double rayAngle, double *h_hit_x, double *h_hit_y);
double 		get_v_distance(t_data *data, double rayAngle, double *v_hit_x, double *v_hit_y);
void 		ray(t_data *data, double rayAngle);
void  		castAllRay(t_data *data);
int			key_press(int keycode, t_data *data);
void		get_player_position(t_data *data);

//window
int 		create_window(char **map);

// action
void	move_player_down(t_data *data);
void	move_player_right(t_data *data);
void	move_player_left(t_data *data);
void	move_player_up(t_data *data);
void    drawmap(t_data *data);
void    drawplayer(t_data *data);
int is_wall(t_data *data, double y, double x);
float	normalize_angle(float angle);

#endif