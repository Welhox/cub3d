/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:08:23 by clundber          #+#    #+#             */
/*   Updated: 2024/08/28 16:15:18 by tcampbel         ###   ########.fr       */
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
# include <pthread.h> //REMOVE FOR NON BONUS!!

# define DEG_RAD 0.0174532925
# define PI 3.14159265359
# define BUBBLE 0.2
# define MMS 3 //minimap scale
# define SHADE 4
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

typedef struct s_sprite
{
	float		x;
	float		y;
	float		dist;
	float		angle;
	float		scale;
	float		height;
	float		width;
	mlx_image_t	*frame[10];
}	t_sprite;

typedef struct s_txt
{
	float	wall_x;
	float	wall_y;
	int		wall_face;
	float	pos;
	float	step;
	int		height;
	bool	hori_door;
	bool	vert_door;
	bool	door;
	float	shade;
	int		wall_height; //total wall height in pixels
}	t_txt;

typedef struct s_img
{
	mlx_image_t		*mm; //minimap
	mlx_image_t		*mm_wall; //minimap  walls
	mlx_image_t		*mm_floor; //minmap floor
	mlx_image_t		*mm_door; //minimap door
	mlx_image_t		*floor; //backgorund game floor
	mlx_image_t		*floor_txt;
	mlx_image_t		*ceil; //background sky
	mlx_image_t		*ceil_txt;	
	mlx_image_t		*pl; //pl
	mlx_image_t		*ray_grid; //layer for all the rays
	mlx_image_t		*fg; //foreground
	mlx_image_t		*fg_ceiling; //ONLY BONUS
	mlx_image_t		*fg_floor; //ONLY BONUS
	mlx_image_t		*wall_txt[5];
	mlx_image_t		*door;
	mlx_image_t		*sprite;
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
	int		pixel_row;
	bool	hori_end;
	bool	vert_end;
	pthread_t	floor_thread; //BONUS ONLY (prolly should make init)
	pthread_t	ceiling_thread; //BONUS ONLY
}	t_ray;

typedef struct s_pl
{
	float		pl_x;
	float		pl_y;
	float		p_orientation;
	float		step_x;
	float		step_y;
	float		bub_x;
	float		bub_y;
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
	float		ms_x; //mouse x pos
	float		ms_y; // mouse y pos
	float		prev_x; //previous x position of cursor
	float		left; // left edge of window
	float		right; // right edge of window
	bool		input;
	float		*depth;
	t_pl		*pl;
	t_ray		*ray;
	t_img		*img;
	t_txt		*txt;
	t_sprite	*sprites;
	mlx_t		*mlx;
	float		scale;
	int			*height;
	int			s_count;
	int			c_frame; //current frame;
}	t_data;

//INIT

void	init_all(t_data *data, t_ray *ray, t_pl *pl, t_txt *txt);
void	init_img_text(t_img *img);

//UTILS

float		get_scale(t_data *data);
int			ft_atoi_cubd(const char *str);
float		fl_max(float a, float b);
float		fl_min(float a, float b);

//THREADS

void		safe_thread(t_data *data, pthread_t *thread, void *func, void *param);
void		safe_join(t_data *data, pthread_t thread);

//DDA
void		get_dist(t_data *data, t_ray *ray);
int			update_ray_dist(t_ray *ray, int flag);
void		vertical_delta(t_ray *ray);
void		horizontal_delta(t_ray *ray);
void		first_horizontal(t_data *data, t_ray *ray);
void		first_vertical(t_data *data, t_ray *ray);

//RAYCASTING, COLOURS, RENDERING

int			get_txt_color(mlx_image_t *img, int x, int y, float shade);
int			make_color(int r, int g, int b, int a);
void		mm_render(t_data *data, t_pl *pl, t_img *img);
void		minimap(t_data *data, t_img *img);
void		color_image(mlx_image_t *image, int color);
void		ray_main(void *param);
void		update_mm_pl(t_data *data, t_pl *pl);
mlx_image_t	*use_txt(t_data *data);
void		shade_factor(t_data *data);
void		paint_row(t_data *data, t_ray *ray, int pixel_row, mlx_image_t *img);
void		paint_wall(t_data *data, t_ray *ray, int pixel_row, mlx_image_t *img);
void		paint_floor(void *arg);
void		paint_ceiling(void *arg);
void		mm_rayprint(t_data *data, t_ray *ray, t_pl *pl);

//SPRITES

void		sprite(/* void *arg */t_data *data, t_ray *ray, t_sprite *duck);
void		sprite_count(t_data *data, char *map_str);
void		set_sprite_pos(t_data *data, int y, int x);

//MOVEMENT

void	keypress(void *param);
void	move_pl(t_data *data, t_pl *pl, t_key key);
void	fix_orientation(float *orientation);
int		ft_collision(t_data *data, float y, float x);
void	toggle_door(t_data *data, t_pl *pl);
void	mouse_callback(double x, double y, void *param);
void	update_mouse(void *param);

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
int		ft_isspace(char c);
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
