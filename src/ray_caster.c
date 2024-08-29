/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:08:28 by clundber          #+#    #+#             */
/*   Updated: 2024/08/14 1 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mm_rayprint(t_data *data, t_ray *ray, t_pl *pl)
{
	int		i;
	float	x;
	float	y;
	float	scaled_dist;
	float	scaled_rend_dist;

	i = 0;
	scaled_dist = ray->distance * data->scale;
	scaled_rend_dist = data->render_dist * data->scale;
	while (i < scaled_dist && i < scaled_rend_dist)
	{
		x = (pl->pl_x * data->scale) - i * sin(ray->orient - (90 * DEG_RAD));
		y = (pl->pl_y * data->scale) + i * cos(ray->orient - (90 * DEG_RAD));
		safe_pixel(data->img->ray_grid, x, y, make_color(255, 0, 0, 200));
		i++;
	}
}

void	paint_ceiling(void *arg)//, t_ray *ray, int pixel_row)
{
	int		y;
	float	floor_x;
	float	floor_y;
	float	row_distance;
	float	fl_txt_x;
	float	fl_txt_y;
	t_data	*data;
	int		pixel_row;
	float	shade;

	pixel_row = 0;
	data = arg;
	float ray_orient = data->pl->p_orientation - ((data->fov / 2) * DEG_RAD);
	float ray_offset = (data->fov / data->s_width) * DEG_RAD;
	// if (data->ray->corr_dist > data->render_dist)
	// 	y = (data->s_height / 2.0);
	// else
	// 	y = (data->s_height / 2.0) - (data->txt->wall_height / 2);
	while (pixel_row < data->s_width)	
	{	
		if (data->depth[pixel_row] > data->render_dist)
			y = (data->s_height / 2.0);
		else
			y = (data->s_height / 2.0) - (data->height[pixel_row] / 2); 
		//y = data->s_height / 2.0;
		while (y >= 0)
		{
			row_distance = (data->ray->proj_plane / 2.0) / ((data->s_height / 2.0) - (float)y) / (cos(ray_orient - data->pl->p_orientation));
			shade = ((float)1 / row_distance) * SHADE;
			if (shade > 1)
				shade = 1;
			floor_x = data->pl->pl_x + (row_distance * cos(ray_orient));
			floor_y = data->pl->pl_y + (row_distance * sin(ray_orient));	
			fl_txt_x = (int)((floor_x + floorf(floor_x)) * data->img->ceil_txt->width) % data->img->ceil_txt->width;
			fl_txt_y = (int)((ceil(floor_y) - floor_y) * data->img->ceil_txt->height) % data->img->ceil_txt->height;
			safe_pixel(data->img->fg_ceiling, pixel_row, y, get_txt_color(data->img->ceil_txt, fl_txt_x, fl_txt_y, shade));
			y--;
		}
		ray_orient += ray_offset;
		pixel_row++;
	}
}

void	paint_floor(void *arg)//t_data *data, t_ray *ray, int pixel_row)
{
	int 	y;
	float	floor_x;
	float	floor_y;
	float	row_distance;
	float	fl_txt_x;
	float	fl_txt_y;
	t_data	*data;
	int		pixel_row;
	float	shade;

	pixel_row = 0;
	data = arg;
	float ray_orient = data->pl->p_orientation - ((data->fov / 2) * DEG_RAD);
	float ray_offset = (data->fov / data->s_width) * DEG_RAD;
	while (pixel_row < data->s_width)	
	{	
		if (data->depth[pixel_row] > data->render_dist)
			y = (data->s_height / 2.0);
		else
			y = (data->s_height / 2.0) + (data->height[pixel_row] / 2); 
		//y = data->s_height / 2.0; 
		while (y < data->s_height)
		{
			row_distance = (data->ray->proj_plane / 2.0) / ((float)y - (data->s_height / 2.0)) / (cos(ray_orient - data->pl->p_orientation));
			shade = ((float)1 / row_distance) * SHADE;
			if (shade > 1)
				shade = 1;
			floor_x = data->pl->pl_x + (row_distance * cos(ray_orient));
			floor_y = data->pl->pl_y + (row_distance * sin(ray_orient));	
			fl_txt_x = (int)((floor_x + floorf(floor_x)) * data->img->floor_txt->width) % data->img->floor_txt->width;
			fl_txt_y = (int)((floor_y + floorf(floor_y)) * data->img->floor_txt->height) % data->img->floor_txt->height;
			safe_pixel(data->img->fg_floor, pixel_row, y, get_txt_color(data->img->floor_txt, fl_txt_x, fl_txt_y, shade));
			y++;
		}
		ray_orient += ray_offset;
		pixel_row++;
	}
}

void	paint_wall(t_data *data, t_ray *ray, int pixel_row, mlx_image_t *img)
{
	int start;
	int	y;

	start = (data->s_height / 2) - (data->txt->wall_height / 2);
	y = start;
	if (ray->corr_dist > data->render_dist)
		return ;
	data->txt->pos = ((float)start - ((float)data->s_height / 2) + ((float)data->txt->height / 2)) * data->txt->step;
	while (y < (start + data->txt->wall_height))
	{
		data->txt->wall_y = (int)data->txt->pos % img->height;
		data->txt->pos += data->txt->step;
		safe_pixel(data->img->fg, pixel_row, y, get_txt_color(img, floor(data->txt->wall_x * img->width), data->txt->wall_y, data->txt->shade));
		y++;
	}
}

void	paint_row(t_data *data, t_ray *ray, int pixel_row, mlx_image_t *img)
{
	ray->corr_dist = ray->distance * cos(data->pl->p_orientation - ray->orient);
	data->txt->wall_height = (64 / (ray->corr_dist * 64)) * ray->proj_plane;
	data->txt->step = 1.0 * (float)(img->height / (float)data->txt->wall_height);
	data->txt->height = data->txt->wall_height;
	data->height[pixel_row] = data->txt->wall_height;
	if (data->txt->wall_height > data->s_height)
		data->txt->wall_height = data->s_height;


	paint_wall(data, ray, pixel_row, img);
}
