/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:08:28 by clundber          #+#    #+#             */
/*   Updated: 2024/07/23 15:35:57 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void first_vertical(t_data *data, t_ray *ray)
{
	if (!(ray->ray_orient == PI / 2 || ray->ray_orient == 1.5 * PI))
	{
		if (ray->ray_orient < 1.5 * PI  && ray->ray_orient > PI / 2) // going left
		{
			
			ray->vert_x = floor(data->player_x);
			ray->vert_y = data->player_y + ((data->player_x - ray->vert_x) * tan(ray->ray_orient));
		}
		else
		{
			ray->vert_x = ceil(data->player_x);
			ray->vert_y = data->player_y + ((ray->vert_x - data->player_x) * -tan(ray->ray_orient));
		}
		ray->vertical_dist = sqrt(pow(data->player_x - ray->vert_x, 2) + pow(data->player_y - ray->vert_y, 2));
	}
	else
		ray->vertical_dist = data->fov_depth + 42; //redundant, need to remove later
}

static void	first_horizontal(t_data *data, t_ray *ray)
{	
	if (!(ray->ray_orient == 0 || ray->ray_orient == PI || ray->ray_orient == (2 * PI)))
	{
		if (ray->ray_orient > PI) // going up
		{	
			ray->hori_y = floor(data->player_y);
			ray->hori_x = data->player_x + ((data->player_y - ray->hori_y) / -tan(ray->ray_orient));
		}
		else
		{
			ray->hori_y = ceil(data->player_y);
			ray->hori_x = data->player_x + ((ray->hori_y - data->player_y) / tan(ray->ray_orient));
		}
		ray->horizontal_dist = sqrt(pow(data->player_x - ray->hori_x, 2) + pow(data->player_y - ray->hori_y, 2));
	}
	else
		ray->horizontal_dist = data->fov_depth + 42; //redundant, need to remove later
}
//horizontal lines = y, vertical lines = x
void	get_dist(t_data *data, t_ray *ray)
{
	first_horizontal(data, ray);
	first_vertical(data, ray);
	if (ray->horizontal_dist < ray->vertical_dist)
		ray->distance = ray->horizontal_dist;
	else
		ray->distance = ray->vertical_dist;
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
	//printf("p->orient = %f\n", data->p_orientation / DEG_RAD);
 	while (i < 1 * data->scale)
	{
		safe_pixel(data->images->ray_grid, (data->player_x * data->scale) - i * sin(data->p_orientation - (90 * DEG_RAD)), (data->player_y * data->scale) + i * cos(data->p_orientation - (90 * DEG_RAD)), make_color(255, 0, 0, 255));
		i++;
	}
}

void	mm_rayprint(t_data *data)
{
	int		i;
	float	x;
	float	y;
	
	i = 0;
	while (i < data->ray->distance * data->scale)
	{
		x = (data->player_x * data->scale) - i * sin(data->p_orientation - (90 * DEG_RAD));
		y = (data->player_y * data->scale) + i * cos(data->p_orientation - (90 * DEG_RAD));
		safe_pixel(data->images->ray_grid, x, y, make_color(0, 0, 255, 255));
		i++;
	}
}

void	ray_main(void *param)
{
	t_data	*data;

	data = param;
	data->ray->ray_orient = data->p_orientation;
	get_dist(data, data->ray);
	mlx_delete_image(data->mlx, data->images->ray_grid);
	data->images->ray_grid = mlx_new_image(data->mlx, data->s_width, data->s_height);
	if (!data->images->ray_grid)
		armageddon(data, "image mallocing failed");
	mlx_image_to_window(data->mlx, data->images->ray_grid, 0, 0);
	//print_penis(data);
	mm_rayprint(data);
}
