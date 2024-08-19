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

void	paint_ceiling(t_data *data, t_ray *ray, int pixel_row)
{
	int		y;
	float	floor_x;
	float	floor_y;
	float	row_distance;
	float	fl_txt_x;
	float	fl_txt_y;

	if (ray->corr_dist > data->render_dist)
		y = (data->s_height / 2.0);
	else
		y = (data->s_height / 2.0) - (data->txt->wall_height / 2);
	while (y >= 0)
	{
		row_distance = (ray->proj_plane / 2.0) / ((data->s_height / 2.0) - (float)y) / (cos(ray->orient - data->pl->p_orientation));
		data->txt->shade = ((float)1 / row_distance) * SHADE;
		if (data->txt->shade >= 1)
			data->txt->shade = 1;
		floor_x = data->pl->pl_x + (row_distance * cos(ray->orient));
		floor_y = data->pl->pl_y + (row_distance * sin(ray->orient));	
		fl_txt_x = (int)((floor_x + floorf(floor_x)) * data->img->ceil_txt->width) % data->img->ceil_txt->width;
		fl_txt_y = (int)((ceil(floor_y) - floor_y) * data->img->ceil_txt->height) % data->img->ceil_txt->height;
		safe_pixel(data->img->fg, pixel_row, y, get_txt_color(data->img->ceil_txt, fl_txt_x, fl_txt_y, data->txt->shade));
		y--;
	}
}

void	paint_floor(t_data *data, t_ray *ray, int pixel_row)
{
	int 	y;
	float	floor_x;
	float	floor_y;
	float	row_distance;
	float	fl_txt_x;
	float	fl_txt_y;

	if (ray->corr_dist > data->render_dist)
		y = (data->s_height / 2.0);
	else
		y = (data->s_height / 2.0) + (data->txt->wall_height / 2);
	while (y < data->s_height)
	{		
		row_distance = (ray->proj_plane / 2.0) / ((float)y - (data->s_height / 2.0)) / (cos(ray->orient - data->pl->p_orientation));
		data->txt->shade = ((float)1 / row_distance) * SHADE;
		if (data->txt->shade >= 1)
			data->txt->shade = 1;
		floor_x = data->pl->pl_x + (row_distance * cos(ray->orient));
		floor_y = data->pl->pl_y + (row_distance * sin(ray->orient));	
		fl_txt_x = (int)((floor_x + floorf(floor_x)) * data->img->floor_txt->width) % data->img->floor_txt->width;
		fl_txt_y = (int)((floor_y + floorf(floor_y)) * data->img->floor_txt->height) % data->img->floor_txt->height;
		safe_pixel(data->img->fg, pixel_row, y, get_txt_color(data->img->floor_txt, fl_txt_x, fl_txt_y, data->txt->shade));
		y++;
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
	if (data->txt->wall_height > data->s_height)
		data->txt->wall_height = data->s_height;
	paint_wall(data, ray, pixel_row, img);
	paint_ceiling(data, ray, pixel_row);
	paint_floor(data, ray, pixel_row);
}

void	refresh_img(t_data *data, t_img *img)
{
	mlx_delete_image(data->mlx, img->ray_grid);
	mlx_delete_image(data->mlx, img->fg);
	safe_image(data, data->s_width / MMS, data->s_height / MMS, &img->ray_grid);
	safe_image(data, data->s_width, data->s_height, &img->fg);
}

void	wall_face(t_ray *ray, t_txt *txt)
{
	if (ray->horizontal_dist < ray->vertical_dist)
	{
		if (ray->orient > PI)
			txt->wall_face = NORTH;
		else
		{
			txt->wall_face = SOUTH;
			txt->wall_x = 1 - txt->wall_x;
		}
		if (txt->hori_door == true)
			txt->door = true;
	}
	else
	{
		if (ray->orient < 1.5 * PI && ray->orient > PI / 2) // going left
		{
			txt->wall_face = WEST;
			txt->wall_x = 1 - txt->wall_x;
		}
		else
			txt->wall_face = EAST;
		if (txt->vert_door == true)
			txt->door = true;
	}
}

void	render(t_data *data, t_ray *ray, int pixel_row)
{
	data->txt->hori_door = false;
	data->txt->vert_door = false;
	data->txt->door = false;
	fix_orientation(&ray->orient);
	get_dist(data, data->ray);
	shade_factor(data);
	wall_face(ray, data->txt);
	update_mm_pl(data, data->pl);
	if (pixel_row % 30 == 0)
		mm_rayprint(data, ray, data->pl);
	paint_row(data, ray, pixel_row, use_txt(data));
}

void	ray_main(void *param)
{
	t_data	*data;
	t_ray	*ray;
	float	ray_offset;
	int		pixel_row;

	pixel_row = 0;
	data = param;
	ray = data->ray;
	if (data->input == true)
	{
		keypress(data);
		update_mouse(data);
		ray_offset = (data->fov / data->s_width) * DEG_RAD;
		ray->orient = data->pl->p_orientation - ((data->fov / 2) * DEG_RAD);
		refresh_img(data, data->img);
		while (pixel_row < data->s_width)
		{
			render(data, ray, pixel_row);
			ray->orient += ray_offset;
			pixel_row++;
		}
		mlx_image_to_window(data->mlx, data->img->ray_grid, 0, 0);
		mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
		mlx_set_instance_depth(data->img->fg->instances, 2);	
		data->input = false;
	}
	sprite(data, ray);
}
