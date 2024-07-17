/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:08:23 by clundber          #+#    #+#             */
/*   Updated: 2024/07/17 11:36:04 by tcampbel         ###   ########.fr       */
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

# define DEG_RAD 0.0174532925
# define PI 3.14159265359

typedef struct s_data t_data;

typedef struct s_images
{
	mlx_image_t	*mm; //minimap
	mlx_image_t	*bg; //background
	mlx_image_t	*pl; //player
}	t_images;

typedef struct s_ray
{
	t_data 	*data;
	float	ray_x;
	float	ray_y;
	float	ray_orient;
}	t_ray;

typedef	struct s_data
{
	char 		**map;
	int			mapstart;
	float		player_x;
	float		player_y;
	float		p_orientation;
	float		map_x_border;
	float		map_y_border;
	int			floor[4];
	int			ceiling[4];
	char		*wall_text[5]; //0N, 1E, 2S, 3W
	float		s_height;
	float		s_width;
	float		fov;
	float		fov_depth;
	t_ray		*ray;
	t_images	*images;
	mlx_t		*mlx;
	
	
}	t_data;


int		parsing(int argc, char **argv, t_data *data);
void	ft_nullfree(char *str);
int		ret_error(char *str);
void    init_all(t_data *data, t_ray *ray);
void	update_params(t_data *data);
void	mlx_main(t_data *data, t_ray *ray);
int32_t colourise(int32_t r, int32_t g, int32_t b, int32_t a);


# endif