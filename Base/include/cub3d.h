/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:08:23 by clundber          #+#    #+#             */
/*   Updated: 2024/08/28 14:45:05 by tcampbel         ###   ########.fr       */
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

# define DEG_RAD 0.0174532925
# define PI 3.14159265359
# define HORI 1
# define VERT 2

typedef struct s_data	t_data;

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
	int		wall_height; //total wall height in pixels
}	t_txt;

typedef struct s_img
{
	mlx_image_t		*floor; //backgorund game floor
	mlx_image_t		*ceil; //background sky
	mlx_image_t		*fg; //foreground
	mlx_image_t		*wall_txt[5];
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
	float		step_x;
	float		step_y;
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
	char		*wall_text[5]; //0N, 1E, 2S, 3W    //rename to wall_path
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

void	init_all(t_data *data, t_ray *ray, t_pl *pl, t_txt *txt);
void	init_img_text(t_img *img);

//UTILS

int		ft_isspace(char c);
int		ft_atoi_cubd(const char *str);

//DDA
void	get_dist(t_data *data, t_ray *ray);
int		update_ray_dist(t_ray *ray, int flag);
void	vertical_delta(t_ray *ray);
void	horizontal_delta(t_ray *ray);
void	first_horizontal(t_data *data, t_ray *ray);
void	first_vertical(t_data *data, t_ray *ray);

//RAYCASTING, COLOURS, RENDERING

int			get_txt_color(mlx_image_t *img, int x, int y, float shade);
int			make_color(int r, int g, int b, int a);
void		color_image(mlx_image_t *image, int color);
void		ray_main(void *param);
mlx_image_t	*use_txt(t_data *data);

//MOVEMENT

void	keypress(void *param);
void	move_pl(t_data *data, t_pl *pl, t_key key);
void	fix_orientation(float *orientation);
int		ft_collision(t_data *data, float y, float x);

//MLX

void	update_params(t_data *data, t_ray *ray);
void	mlx_main(t_data *data);
void	safe_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void	safe_image(t_data *data, uint32_t w, uint32_t h, mlx_image_t **img);
void	safe_texture(t_data *data, mlx_texture_t **img, char *path);
void	safe_txt_to_img(t_data *data, mlx_texture_t *text, mlx_image_t **img);
void	safe_delete_img(t_data *data, mlx_image_t *img);

//PARSING

int		parsing(int argc, char **argv, t_data *data);
int		map_parse(char *map_str, t_data *data);
char	*get_path(char *line);
int		check_name(char *str);
int		check_line(char *line, t_data *data);
int		get_color(int *arr, char *str);
int		extract_data(char *arg, t_data *data);
int		validate_map(t_data *data);

//FREE & ERROR

int		ft_nullfree(char *str, int err);
int		ret_error(char *str);
void	free_img(t_data *data, t_img *img);
void	ft_mapfree(char **array);
void	armageddon(t_data *data, char *error);

#endif
