/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:08:23 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 15:38:51 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> 	// for printf, perror
# include <unistd.h> 	// for write, close, read
# include <fcntl.h>		// for open
# include <stdlib.h> 	// for malloc, free, exit
# include <string.h> 	// for strerror
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>

# define DG_RD 0.0174532925
# define PI 3.14159265359
# define HORI 1
# define VERT 2

typedef struct s_data	t_data;
typedef mlx_image_t		t_mlx_img;
typedef mlx_texture_t	t_mlx_txt;

typedef enum e_key
{
	LEFT,
	RIGHT,
	FORWARD,
	BACK,
	S_LEFT,
	S_RIGHT
}	t_key;

typedef enum e_wall
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_wall;

typedef struct s_txt
{
	float	wall_x;
	float	wall_y;
	int		wall_face;
	float	pos;
	float	step;
	int		height;
	int		wall_height;
}	t_txt;

typedef struct s_img
{
	t_mlx_img		*floor;
	t_mlx_img		*ceil;
	t_mlx_img		*fg;
	t_mlx_img		*wall_txt[5];
	mlx_t			*mlx;
}	t_img;

typedef struct s_ray
{
	t_data	*data;
	float	hori_x;
	float	hori_y;
	float	vert_x;
	float	vert_y;
	float	h_delta_x;
	float	h_delta_y;
	float	v_delta_x;
	float	v_delta_y;
	float	horizontal_dist;
	float	vertical_dist;
	float	orient;
	float	distance;
	float	h_step_dist;
	float	v_step_dist;
	float	proj_plane;
	float	corr_dist;
	bool	hori_end;
	bool	vert_end;
}	t_ray;

typedef struct s_pl
{
	float		pl_x;
	float		pl_y;
	float		p_orientation;
	float		stp_x;
	float		stp_y;
	t_data		*data;
}	t_pl;

typedef struct s_data
{
	char		**map;
	int			mapstart;
	float		map_x_border;
	float		map_y_border;
	int			floor[4];
	int			ceil[4];
	char		*wall_text[5];
	float		s_height;
	float		s_width;
	float		fov;
	float		render_dist;
	t_pl		*pl;
	t_ray		*ray;
	t_img		*img;
	t_txt		*txt;
	mlx_t		*mlx;
	float		scale;
}	t_data;

//INIT

void		init_all(t_data *data, t_ray *ray, t_pl *pl, t_txt *txt);
void		init_img_text(t_img *img);

//UTILS

int			ft_isspace(char c);
int			ft_atoi_cubd(const char *str);

//DDA
void		get_dist(t_data *data, t_ray *ray);
int			update_ray_dist(t_ray *ray, int flag);
void		vertical_delta(t_ray *ray);
void		horizontal_delta(t_ray *ray);
void		first_horizontal(t_data *data, t_ray *ray);
void		first_vertical(t_data *data, t_ray *ray);

//RAYCASTING, COLOURS, RENDERING

int			get_txt_color(t_mlx_img *img, int x, int y, float shade);
int			make_color(int r, int g, int b, int a);
void		color_image(t_mlx_img *image, int color);
void		ray_main(void *param);
t_mlx_img	*use_txt(t_data *data);
void		refresh_img(t_data *data, t_img *img);

//MOVEMENT

void		keypress(void *param);
void		move_pl(t_data *data, t_pl *pl, t_key key);
void		fix_orientation(float *orientation);
int			ft_collision(t_data *data, float y, float x);

//MLX

void		update_params(t_data *data, t_ray *ray);
void		mlx_main(t_data *data);
void		safe_pixel(t_mlx_img *img, uint32_t x, uint32_t y, uint32_t color);
void		safe_image(t_data *data, uint32_t w, uint32_t h, t_mlx_img **img);
void		safe_texture(t_data *data, t_mlx_txt **img, char *path);
void		safe_txt_to_img(t_data *data, t_mlx_txt *text, t_mlx_img **img);
void		safe_delete_img(t_data *data, t_mlx_img *img);

//PARSING

int			parsing(int argc, char **argv, t_data *data);
int			map_parse(char *map_str, t_data *data);
char		*get_path(char *line);
int			check_name(char *str);
int			check_line(char *line, t_data *data);
int			get_color(int *arr, char *str);
int			extract_data(char *arg, t_data *data);
int			validate_map(t_data *data);

//FREE & ERROR

int			ft_nullfree(char *str, int err);
int			ret_error(char *str);
void		free_img(t_data *data, t_img *img);
void		ft_mapfree(char **array);
void		armageddon(t_data *data, char *error);

#endif
