/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_two_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:19:33 by tcampbel          #+#    #+#             */
/*   Updated: 2024/09/03 14:25:57 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	pixel_ceiling(t_data *data, float ray_orient, int px_row, int y)
{
	float	tx[2];
	float	floor[2];
	float	row_distance;
	float	shade;
	int		color;

	row_distance = (data->ray->proj_plane / 2.0) / ((data->s_height / 2.0) \
						- (float)y) / (cos(ray_orient - data->pl->orient));
	shade = ((float)1 / row_distance) * SHADE;
	if (shade > 1)
		shade = 1;
	floor[X] = data->pl->pl_x + (row_distance * cos(ray_orient));
	floor[Y] = data->pl->pl_y + (row_distance * sin(ray_orient));
	tx[X] = (int)((floor[X] + floorf(floor[X])) * data->img->ceil_txt->width) \
												% data->img->ceil_txt->width;
	tx[Y] = (int)((ceil(floor[Y]) - floor[Y]) * data->img->ceil_txt->height) \
												% data->img->ceil_txt->height;
	color = get_txt_color(data->img->ceil_txt, tx[X], tx[Y], shade);
	safe_pixel(data->img->fg_ceiling, px_row, y, color);
}

void	paint_ceiling(void *arg)
{
	int		y;
	t_data	*data;
	int		pixel_row;
	float	ray_orient;
	float	ray_offset;

	pixel_row = -1;
	data = arg;
	ray_orient = data->pl->orient - ((data->fov / 2) * DG_RD);
	ray_offset = (data->fov / data->s_width) * DG_RD;
	while (++pixel_row < data->s_width)
	{
		if (data->depth[pixel_row] > data->render_dist)
			y = (data->s_height / 2.0);
		else
			y = (data->s_height / 2.0) - (data->height[pixel_row] / 2);
		while (y >= 0)
		{
			pixel_ceiling(data, ray_orient, pixel_row, y);
			y--;
		}
		ray_orient += ray_offset;
	}
}

void	pixel_floor(t_data *data, float ray_orient, int px_row, int y)
{
	float	floor[2];
	float	row_distance;
	float	tx[2];
	float	shade;
	int		color;

	row_distance = (data->ray->proj_plane / 2.0) / ((float)y - \
		(data->s_height / 2.0)) / (cos(ray_orient - data->pl->orient));
	shade = ((float)1 / row_distance) * SHADE;
	if (shade > 1)
		shade = 1;
	floor[X] = data->pl->pl_x + (row_distance * cos(ray_orient));
	floor[Y] = data->pl->pl_y + (row_distance * sin(ray_orient));
	tx[X] = (int)((floor[X] + floorf(floor[X])) * data->img->floor_txt->width) \
										% data->img->floor_txt->width;
	tx[Y] = (int)((floor[Y] + floorf(floor[Y])) * data->img->floor_txt->height) \
												% data->img->floor_txt->height;
	color = get_txt_color(data->img->floor_txt, tx[X], tx[Y], shade);
	safe_pixel(data->img->fg_floor, px_row, y, color);
}

void	paint_floor(void *arg)
{
	int		y;
	t_data	*data;
	int		pixel_row;
	float	ray_orient;
	float	ray_offset;

	pixel_row = 0;
	data = arg;
	ray_orient = data->pl->orient - ((data->fov / 2) * DG_RD);
	ray_offset = (data->fov / data->s_width) * DG_RD;
	while (pixel_row < data->s_width)
	{
		if (data->depth[pixel_row] > data->render_dist)
			y = (data->s_height / 2.0);
		else
			y = (data->s_height / 2.0) + (data->height[pixel_row] / 2);
		while (y < data->s_height)
		{
			pixel_floor(data, ray_orient, pixel_row, y);
			y++;
		}
		ray_orient += ray_offset;
		pixel_row++;
	}
}
