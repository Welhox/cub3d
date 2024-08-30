/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:58 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 17:47:34 by tcampbel         ###   ########.fr       */
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
		x = (pl->pl_x * data->scale) - i * sin(ray->orient - (90 * DG_RD));
		y = (pl->pl_y * data->scale) + i * cos(ray->orient - (90 * DG_RD));
		safe_pixel(data->img->ray_grid, x, y, make_color(255, 0, 0, 200));
		i++;
	}
}

void	paint_wall(t_data *data, t_ray *ray, int pixel_row, mlx_image_t *img)
{
	t_txt		*txt;
	mlx_image_t	*fg;
	int			start;
	int			y;
	int			color;

	txt = data->txt;
	fg = data->img->fg;
	start = (data->s_height / 2) - (txt->wall_height / 2);
	y = start;
	if (ray->corr_dist > data->render_dist)
		return ;
	data->txt->pos = ((float)start - ((float)data->s_height / 2) + \
					((float)data->txt->height / 2)) * txt->step;
	while (y < (start + txt->wall_height))
	{
		txt->wall_y = (int)txt->pos % img->height;
		txt->pos += txt->step;
		color = get_txt_color(img, floor(txt->wall_x * img->width), txt->wall_y, txt->shade);
		safe_pixel(fg, pixel_row, y, color);
		y++;
	}
}

void	paint_row(t_data *data, t_ray *ray, int pixel_row, mlx_image_t *img)
{
	ray->corr_dist = ray->distance * cos(data->pl->orient - ray->orient);
	data->txt->wall_height = (64 / (ray->corr_dist * 64)) * ray->proj_plane;
	data->txt->step = 1 * (float)(img->height / (float)data->txt->wall_height);
	data->txt->height = data->txt->wall_height;
	data->height[pixel_row] = data->txt->wall_height;
	if (data->txt->wall_height > data->s_height)
		data->txt->wall_height = data->s_height;
	paint_wall(data, ray, pixel_row, img);
}
