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
		safe_pixel(data->img->fg, pixel_row, y, get_txt_color(img, floor(data->txt->wall_x * img->width), data->txt->wall_y, 1));
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
}

void	refresh_img(t_data *data, t_img *img)
{
	mlx_delete_image(data->mlx, img->fg);
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
	}
}

void	render(t_data *data, t_ray *ray, int pixel_row)
{
	fix_orientation(&ray->orient);
	get_dist(data, data->ray);
	wall_face(ray, data->txt);
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
	ray_offset = (data->fov / data->s_width) * DEG_RAD;
	ray->orient = data->pl->p_orientation - ((data->fov / 2) * DEG_RAD);
	refresh_img(data, data->img);
	while (pixel_row < data->s_width)
	{
		render(data, ray, pixel_row);
		ray->orient += ray_offset;
		pixel_row++;
	}
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
	mlx_set_instance_depth(data->img->fg->instances, 2);
}
