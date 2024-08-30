/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:50:40 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 17:08:39 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	refresh_img(t_data *data, t_img *img)
{
	mlx_delete_image(data->mlx, img->ray_grid);
	mlx_delete_image(data->mlx, img->fg);
	if (data->img->sprite)
		mlx_delete_image(data->mlx, data->img->sprite);
	if (img->fg_ceiling != NULL)
		mlx_delete_image(data->mlx, img->fg_ceiling);
	if (img->fg_floor != NULL)
		mlx_delete_image(data->mlx, img->fg_floor);
	if (data->sprites != NULL)
		safe_image(data, data->s_width, data->s_height, &data->img->sprite);
	safe_image(data, data->s_width / MMS, data->s_height / MMS, &img->ray_grid);
	safe_image(data, data->s_width, data->s_height, &img->fg);
	safe_image(data, data->s_width, data->s_height, &img->fg_ceiling);
	safe_image(data, data->s_width, data->s_height, &img->fg_floor);
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
		check_door_or_cage(txt, ray);
	}
	else
	{
		if (ray->orient < 1.5 * PI && ray->orient > PI / 2)
		{
			txt->wall_face = WEST;
			txt->wall_x = 1 - txt->wall_x;
		}
		else
			txt->wall_face = EAST;
		check_door_or_cage(txt, ray);
	}
}

void	render(t_data *data, t_ray *ray, int pixel_row, float offset)
{
	data->txt->hori_door = false;
	data->txt->vert_door = false;
	data->txt->door = false;
	data->txt->hori_cage = false;
	data->txt->vert_cage = false;
	data->txt->cage = false;
	fix_orientation(&ray->orient);
	get_dist(data, data->ray);
	shade_factor(data);
	wall_face(ray, data->txt);
	update_mm_pl(data, data->pl);
	if (pixel_row % 30 == 0)
		mm_rayprint(data, ray, data->pl);
	data->depth[pixel_row] = ray->distance;
	paint_row(data, ray, pixel_row, use_txt(data));
	ray->orient += offset;
	data->depth[ray->pixel_row] = ray->distance;
}

void	threads_and_windows(t_data *data, t_img *img, t_ray *ray)
{
	if (data->sprites != NULL)
		safe_thread(data, &ray->sprite_thread, &sprite, NULL);
	safe_thread(data, &ray->ceiling_thread, &paint_ceiling, NULL);
	safe_thread(data, &ray->floor_thread, &paint_floor, NULL);
	if (data->sprites != NULL)
		safe_join(data, ray->sprite_thread);
	safe_join(data, ray->ceiling_thread);
	safe_join(data, ray->floor_thread);
	mlx_image_to_window(data->mlx, img->ray_grid, 0, 0);
	mlx_image_to_window(data->mlx, img->fg, 0, 0);
	mlx_image_to_window(data->mlx, img->fg_ceiling, 0, 0);
	mlx_image_to_window(data->mlx, img->fg_floor, 0, 0);
	mlx_set_instance_depth(img->fg->instances, 4);
	mlx_set_instance_depth(img->fg_ceiling->instances, 3);
	mlx_set_instance_depth(img->fg_floor->instances, 2);
}

void	ray_main(void *param)
{
	t_data		*data;
	t_ray		*ray;
	float		ray_offset;

	data = param;
	if (data->end == true)
		return ;
	ray = data->ray;
	ray->pixel_row = -1;
	ray_offset = (data->fov / data->s_width) * DG_RD;
	ray->orient = data->pl->orient - ((data->fov / 2) * DG_RD);
	get_fps(data);
	refresh_img(data, data->img);
	while (++ray->pixel_row < data->s_width)
		render(data, data->ray, ray->pixel_row, ray_offset);
	threads_and_windows(data, data->img, ray);
	ft_memset(data->depth, 0, data->s_width);
	ft_memset(data->height, 0, data->s_width);
}
