/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:44:28 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/06/01 18:47:07 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"

typedef struct s_map
{
	int		number_of_line;
	int		map_parsing_started;
	char	*no_input;
	char	*so_input;
	char	*we_input;
	char	*ea_input;
	char	*f_input;
	char	*c_input;
	char	**map;
	int		rgb_c[3];
	int		rgb_floor[3];
	char	player;
	double	player_x;
	double	player_y;
	int		pos_x;
	int		pos_y;
}				t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_rcast
{
	double	camera_x;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	plane_x;
	double	plane_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		x;
	int		y;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	perp_wall_dist;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
}				t_rcast;

typedef struct s_cub
{
	t_map		*map;
	t_data		*img[5];
	t_rcast		*rcast;
	int			screen_x;
	int			screen_y;
	void		*mlx_ptr;
	void		*window_ptr;
	double		speed;
	double		rot_speed;
	int			do_raycast;
	int			hundred_i;
	int			hundred_j;
	int			i;
	int			j;
}				t_cub;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define WIDTH			1920
# define HEIGHT			1080
# define FORWARD	    119
# define BACKWARD	    115
# define LEFT		    97
# define RIGHT		    100
# define ROTATE_LEFT    65361
# define ROTATE_RIGHT   65363

int				main(int argc, char **argv);

//gnl_utils
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *str);
size_t			ft_strlen(const char *s);

//gnl
int				get_next_line(int fd, char **line);

//gnl_test
int				test( int **r, char *buf);
int				test2( int **r, char *buf, char **str, int fd);
//free_data.c
void			free_map(t_map *map);
void			free_tab(char **tab);
void			destroy_images(t_data *img[5], void *mlx_ptr);

//parse_data.c
int				parse_data(t_map *map);

//parse_map.c
int				parse_map(t_map *map, int i, int j, int result);

//ft_itoa.c
int				ft_atoi(const char *str);
void			check_is_digit(char *string, int *i, int *j);
int				check_type_text(char *type_input, char *line, char c1, char c2);
void			else_2_func_check_map(char *line, int *error, int fd);
void			check_map_norm(t_map *map, char *line, int *error, int fd);

//move_on_map
int				move_left(t_cub *cub, t_map *map);
int				move_right(t_cub *cub, t_map *map);
int				move_up(t_cub *cub, t_map *map);
int				move_down(t_cub *cub, t_map *map);
void			init_img_player(t_cub *cub);

//change_sight
int				change_sight(t_cub *cub, int type);
int				mouse_hook(int x, int y, t_cub *cub);

//init_window
int				windowinit(t_cub *cub);
int				shutwindow(t_cub *cub);
int				init_img(t_cub *cub);

//put_texture.c
int				put_texture(t_cub *cub);
char			*cut_texture(char *string);
void			raycast(t_cub *cub);

//draw_in_window
int				draw_floor_and_ceiling(t_cub *cub);
void			draw_player(t_cub *cub, double i, double j);
int				draw(t_cub *cub, int a, int b);

//raycasting 
void			raycast(t_cub *cub);
void			raycast_start(t_cub *cub);
void			raycast_launch_ray(t_cub *cub);
void			raycast_ray_hit(t_cub *cub);
void			raycast_end(t_cub *cub);
void			raycast_draw(int tempo_x, t_cub *cub);

//main
int				check_first_char(t_map *map, char *string);
int				all_data_here(t_map *map);
int				key_hook(int keycode, t_cub *cub);

//main_func
int				check_map(char *string, t_map *map);
int				fill_map(t_map *map, char *string);
void			init_map_struct(t_map *map);

//draw_func
unsigned int	get_color_of_image(t_data *data, int x, int y);
int				get_color(int alpha, int r, int g, int b);
int				isplayer(char c);
int				ft_isdigit(int c);
void			my_pixel_put(t_data *data, int x, int y, int color);

#endif