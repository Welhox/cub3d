/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:08:28 by clundber          #+#    #+#             */
/*   Updated: 2024/07/22 14:35:30 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	wall_dist(t_data *data, t_ray *ray)
{
	float	horizontal_dist;
	float	vertical_dist;

	vertical_dist = 0;
	horizontal_dist = 0;
	//HORIZONTAL
	if (ray->ray_orient == 0 || ray->ray_orient == PI || ray->ray_orient == (2 * PI))
		horizontal_dist += data->fov_depth + 100;
	if (ray->ray_orient < 180) //ray facing down, tan is inverted
	{
		ray->ray_y = ceilf(data->player_y);
		ray->ray_x = data->player_x + ((ceilf(data->player_y) - data->player_y) * -tan(ray->ray_orient));
	}
	else //ray facing up
	{
		ray->ray_y = floorf(data->player_y);
		ray->ray_x = data->player_x + ((data->player_y - floorf(data->player_y)) * tan(ray->ray_orient)); 
	}
	//printf("p_x = %f p_y = %f\nr_x = %f r_y = %f\n", data->player_x, data->player_y, ray->ray_x, ray->ray_y);
	
	horizontal_dist = sqrt(pow(data->player_x - ray->ray_y, 2) + pow(data->player_y - ray->ray_y, 2));
	printf("horizontal dist = %f ray orient = %f\n", horizontal_dist, ray->ray_orient);
		printf("player pos = %f\n", data->p_orientation);    
	//map->ray->y_dist = sqrt(pow((float)map->p_pos_x - ray_x, 2) + pow((float)map->p_pos_y - ray_y, 2));

	return (horizontal_dist);

	//VERTICAL
}


void	safe_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (y < img->height && x < img->width)
		mlx_put_pixel(img, x, y, color);
}
// Delete later? :D
void	print_penis(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	printf("p->orient = %f\n", data->p_orientation / DEG_RAD);
 	while (i < 1 * data->scale)
	{
		safe_pixel(data->images->ray_grid, (data->player_x * data->scale) + i * sin(data->p_orientation - (90 * DEG_RAD)), (data->player_y * data->scale) - i * cos(data->p_orientation - (90 * DEG_RAD)), make_color(255, 0, 0, 255));
		//mlx_put_pixel(data->images->ray_grid, (data->player_x * data->scale) + i * sin(data->p_orientation - (90 * DEG_RAD)), (data->player_y * data->scale) - i * cos(data->p_orientation - (90 * DEG_RAD)), make_color(255, 0, 0, 255));
		i++;
	}
}

void	mm_rayprint(t_data *data, float dist)
{
	int	i;
	//int	x;
	//int	y;

	i = 0;
	//x = 0;
	//y = 0;
	
 	while (i < dist * data->scale)
	{
		safe_pixel(data->images->ray_grid, (data->player_x * data->scale) + i * sin(data->p_orientation - (90 * DEG_RAD)), (data->player_y * data->scale) - i * cos(data->p_orientation - (90 * DEG_RAD)), make_color(0, 255, 0, 255));
		i++;
	}
}

void	ray_main(void *param)
{
	float	dist;
	t_data	*data;

	data = param;
	dist = 0;
	data->ray->ray_orient = data->p_orientation;
	//dist = wall_dist(data, data->ray);
	mlx_delete_image(data->mlx, data->images->ray_grid);
	data->images->ray_grid = mlx_new_image(data->mlx, data->s_width, data->s_height);
	if (!data->images->ray_grid)
		armageddon(data, "image mallocing failed");
	mlx_image_to_window(data->mlx, data->images->ray_grid, 0, 0);
	print_penis(data);
	//mm_rayprint(data, dist);
}