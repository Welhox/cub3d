/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:08:28 by clundber          #+#    #+#             */
/*   Updated: 2024/08/07 16:34:55 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void first_vertical(t_data *data, t_ray *ray, bool *end)
{
	if (!(ray->ray_orient == PI / 2 || ray->ray_orient == 1.5 * PI))
	{
		if (ray->ray_orient < 1.5 * PI  && ray->ray_orient > PI / 2) // going left
		{
			
			ray->vert_x = floorf(data->player->pl_x);
			ray->vert_y = data->player->pl_y + ((data->player->pl_x - ray->vert_x) * -tan(ray->ray_orient));
		}
		else
		{
			ray->vert_x = ceilf(data->player->pl_x);
			ray->vert_y = data->player->pl_y + ((ray->vert_x - data->player->pl_x) * tan(ray->ray_orient));
		}
		ray->vertical_dist = sqrt(pow(data->player->pl_x - ray->vert_x, 2) + pow(data->player->pl_y - ray->vert_y, 2));
	}
	else
	{
		ray->vertical_dist = data->render_dist + 42; //redundant, need to remove later
		*end = true; 
	}
}


static void	first_horizontal(t_data *data, t_ray *ray, bool *end)
{	
	if (!(ray->ray_orient == 0 || ray->ray_orient == PI || ray->ray_orient == (2 * PI)))
	{
		if (ray->ray_orient > PI) // going up
		{	
			ray->hori_y = floorf(data->player->pl_y);
			ray->hori_x = data->player->pl_x + ((data->player->pl_y - ray->hori_y) / -tan(ray->ray_orient));
		}
		else
		{
			ray->hori_y = ceilf(data->player->pl_y);
			ray->hori_x = data->player->pl_x + ((ray->hori_y - data->player->pl_y) / tan(ray->ray_orient));
		}
		ray->horizontal_dist = sqrt(pow(data->player->pl_x - ray->hori_x, 2) + pow(data->player->pl_y - ray->hori_y, 2));
	}
	else
	{
		ray->horizontal_dist = data->render_dist + 42; //redundant, need to remove later
		*end = true;
	}
}

void	horizontal_delta(t_ray *ray)
{
	if (ray->ray_orient > PI) // going up
	{
		ray->h_delta_y = -1;
		ray->h_delta_x = 1 / -tan(ray->ray_orient);
	}
	else
	{
		ray->h_delta_y = 1;
		ray->h_delta_x = 1 / tan(ray->ray_orient);
	}
	ray->h_step_dist = sqrt(pow(ray->hori_x - (ray->hori_x + ray->h_delta_x), 2) \
		+ pow(ray->hori_y - (ray->hori_y + ray->h_delta_y), 2));	
}

void	vertical_delta(t_ray *ray)
{
	if (ray->ray_orient < 1.5 * PI  && ray->ray_orient > PI / 2) // going left
	{
		ray->v_delta_x = -1;
		ray->v_delta_y = 1 * -tan(ray->ray_orient);
	}
	else
	{
		ray->v_delta_x = 1;
		ray->v_delta_y = 1 * tan(ray->ray_orient);
	}
	ray->v_step_dist = sqrt(pow(ray->vert_x - (ray->vert_x + ray->v_delta_x), 2) \
		+ pow(ray->vert_y - (ray->vert_y + ray->v_delta_y), 2));
}
//horizontal lines = y, vertical lines = x

void	check_wall(t_data *data, bool *hori_end, bool *vert_end)
{
	if (*hori_end == false)
	{
		if (data->ray->ray_orient > PI)
		{
			if (ft_collision(data, data->ray->hori_y - 1,  data->ray->hori_x))
				*hori_end = true;
			if (ft_collision(data, data->ray->hori_y - 1,  data->ray->hori_x) == 2)
				data->txt->hori_door = true;
		}
		else
		{
			if (ft_collision(data, data->ray->hori_y,  data->ray->hori_x))
				*hori_end = true;
			if (ft_collision(data, data->ray->hori_y,  data->ray->hori_x) == 2)
				data->txt->hori_door = true;			
		}
	}
	if (*vert_end == false)
	{
		if (data->ray->ray_orient > 0.5 * PI && data->ray->ray_orient < 1.5 * PI)
		{
			if (ft_collision(data, data->ray->vert_y,  data->ray->vert_x - 1))
				*vert_end = true;
			if (ft_collision(data, data->ray->vert_y,  data->ray->vert_x - 1) == 2)
				data->txt->vert_door = true;
		}
		else
		{
			if (ft_collision(data, data->ray->vert_y,  data->ray->vert_x))
				*vert_end = true;
			if (ft_collision(data, data->ray->vert_y,  data->ray->vert_x) == 2)
				data->txt->vert_door = true;
		}
	}
}

void	get_dist(t_data *data, t_ray *ray)
{
	bool	vert_end;
	bool	hori_end;

	vert_end = false;
	hori_end = false;
	first_horizontal(data, ray, &hori_end);
	first_vertical(data, ray, &vert_end);
	if (hori_end == false)
		horizontal_delta(ray);
	if (vert_end == false)
		vertical_delta(ray);
	while (42)
	{
		check_wall(data, &hori_end, &vert_end);
		if (ray->horizontal_dist < ray->vertical_dist)
		{
			if (hori_end == false)
			{
				ray->hori_x += ray->h_delta_x;
				ray->hori_y += ray->h_delta_y;
				ray->horizontal_dist += ray->h_step_dist;
			}
			else
				break ;
		}
		else
		{
			if (vert_end == false)
			{
				ray->vert_x += ray->v_delta_x;
				ray->vert_y += ray->v_delta_y;
				ray->vertical_dist += ray->v_step_dist;
			}
			else
				break ;
		}
	}	
	if (ray->horizontal_dist < ray->vertical_dist)
	{
		ray->distance = ray->horizontal_dist;
		data->txt->wall_x = ray->hori_x - floorf(ray->hori_x);
	}
	else
	{
		ray->distance = ray->vertical_dist;
		data->txt->wall_x = ray->vert_y - floorf(ray->vert_y);
	}
}

void	mm_rayprint(t_data *data)
{
	int		i;
	float	x;
	float	y;
	
	i = 0;
	while (i < data->ray->distance * data->scale && i < data->render_dist * data->scale)
	{
		x = (data->player->pl_x * data->scale) - i * sin(data->ray->ray_orient - (90 * DEG_RAD));
		y = (data->player->pl_y * data->scale) + i * cos(data->ray->ray_orient - (90 * DEG_RAD));
		safe_pixel(data->img->ray_grid, x, y, make_color(255, 0, 0, 200));
		i++;
	}
	//mlx_image_to_window(data->mlx, data->img->ray_grid, 0, 0);
}

void	paint_row(t_data *data, t_ray *ray, int	pixel_row, mlx_image_t *img)
{
	int			height;
	int			start;
	int			y;

	ray->corr_dist = ray->distance * cos(data->player->p_orientation - ray->ray_orient);
	if (ray->corr_dist > data->render_dist)
		return ;
	height = (64 / (ray->corr_dist * 64)) * ray->proj_plane;
	data->txt->step = 1.0 * (float)(img->height / (float)height);
	data->txt->height = height;
	if (height > data->s_height)
		height = data->s_height;
	start = (data->s_height / 2) - (height / 2);
	data->txt->pos = ((float)start - ((float)data->s_height / 2) + ((float)data->txt->height / 2)) * data->txt->step;
	y = start;
	while (y < (start + height))
	{
		data->txt->wall_y = (int)data->txt->pos % img->height;
		data->txt->pos += data->txt->step;
			safe_pixel(data->img->fg, pixel_row, y, get_txt_color(img, floor(data->txt->wall_x * img->width), data->txt->wall_y, data->txt->shade));
		y++;
		//printf("text y = %f\n", data->txt->wall_y);
	}
}

void	refresh_img(t_data *data, t_img *img)
{

	mlx_delete_image(data->mlx, img->ray_grid);
	mlx_delete_image(data->mlx, img->fg);
	safe_image(data, data->s_width / mms, data->s_height / mms, &img->ray_grid);
	safe_image(data, data->s_width, data->s_height, &img->fg);
}

void	wall_face(t_ray *ray, t_txt *txt)
{
	if(ray->horizontal_dist < ray->vertical_dist)
	{
		if (ray->ray_orient > PI)
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
		if (ray->ray_orient < 1.5 * PI  && ray->ray_orient > PI / 2) // going left
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

mlx_image_t *use_txt(t_data *data)
{
	if (data->txt->door == true)
		return (data->img->door);
	else
		return (data->img->wall_txt[data->txt->wall_face]);
}

void	shade_factor(t_data *data)
{
	data->txt->shade = ((float)1 / data->ray->distance) * SHADE;
	if (data->txt->shade >= 1)
		data->txt->shade = 1;
}

void	ray_main(void *param)
{
	t_data	*data;
	float	ray_offset;
	t_ray	*ray;
	int		pixel_row;

	pixel_row = 0;
	data = param;
	ray = data->ray;
	ray_offset = (data->fov / data->s_width) * DEG_RAD;
	ray->ray_orient = data->player->p_orientation - ((data->fov / 2) * DEG_RAD);
	refresh_img(data, data->img);
	while (pixel_row < data->s_width)
	{
	data->txt->hori_door = false;
	data->txt->vert_door = false;	
	data->txt->door = false;	
		fix_orientation(&ray->ray_orient);
		get_dist(data, data->ray);
		shade_factor(data);
		wall_face(ray, data->txt);
		update_mm_player(data, data->player);
		if (pixel_row % 10 == 0)
			mm_rayprint(data);
		paint_row(data, ray, pixel_row, use_txt(data));
		ray->ray_orient += ray_offset;
		pixel_row++;
	}
	mlx_image_to_window(data->mlx, data->img->ray_grid, 0, 0);
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
	mlx_set_instance_depth(data->img->fg->instances, 2);
}
