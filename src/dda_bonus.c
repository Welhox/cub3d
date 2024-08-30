/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:08:26 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:38 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_horizontal_wall(t_data *data, t_ray *ray)
{
	if (data->ray->orient > PI)
	{
		if (ft_collision(data, ray->hori_y - 1, ray->hori_x))
			ray->hori_end = true;
		if (ft_collision(data, ray->hori_y - 1, ray->hori_x) == 2)
			data->txt->hori_door = true;
		if (ft_collision(data, ray->hori_y - 1, ray->hori_x) == 5)
			data->txt->hori_cage = true;
	}
	else
	{
		if (ft_collision(data, ray->hori_y, ray->hori_x))
			ray->hori_end = true;
		if (ft_collision(data, ray->hori_y, ray->hori_x) == 2)
			data->txt->hori_door = true;
		if (ft_collision(data, ray->hori_y, ray->hori_x) == 5)
			data->txt->hori_cage = true;
	}
}

void	check_vertical_wall(t_data *data, t_ray *ray)
{
	if (ray->orient > 0.5 * PI && ray->orient < 1.5 * PI)
	{
		if (ft_collision(data, ray->vert_y, ray->vert_x - 1))
			ray->vert_end = true;
		if (ft_collision(data, ray->vert_y, ray->vert_x - 1) == 2)
			data->txt->vert_door = true;
		if (ft_collision(data, ray->vert_y, ray->vert_x - 1) == 5)
			data->txt->vert_cage = true;
	}
	else
	{
		if (ft_collision(data, data->ray->vert_y, data->ray->vert_x))
			ray->vert_end = true;
		if (ft_collision(data, data->ray->vert_y, data->ray->vert_x) == 2)
			data->txt->vert_door = true;
		if (ft_collision(data, data->ray->vert_y, data->ray->vert_x) == 5)
			data->txt->vert_cage = true;
	}
}

void	check_wall(t_data *data, t_ray *ray)
{
	if (ray->hori_end == false)
		check_horizontal_wall(data, ray);
	if (ray->vert_end == false)
		check_vertical_wall(data, ray);
}

void	final_distance(t_data *data, t_ray *ray)
{
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

void	get_dist(t_data *data, t_ray *ray)
{
	ray->vert_end = false;
	ray->hori_end = false;
	first_horizontal(data, ray);
	first_vertical(data, ray);
	if (ray->hori_end == false)
		horizontal_delta(ray);
	if (ray->vert_end == false)
		vertical_delta(ray);
	while (42)
	{
		check_wall(data, ray);
		if (ray->horizontal_dist < ray->vertical_dist)
		{
			if (update_ray_dist(ray, HORI))
				break ;
		}
		else
		{
			if (update_ray_dist(ray, VERT))
				break ;
		}
	}
	final_distance(data, ray);
}
