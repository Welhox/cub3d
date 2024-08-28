/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:52:05 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/28 15:32:45 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	first_vertical(t_data *data, t_ray *ray)
{
	if (!(ray->orient == PI / 2 || ray->orient == 1.5 * PI))
	{
		if (ray->orient < 1.5 * PI && ray->orient > PI / 2)
		{
			ray->vert_x = floorf(data->pl->pl_x);
			ray->vert_y = data->pl->pl_y + \
			((data->pl->pl_x - ray->vert_x) * -tan(ray->orient));
		}
		else
		{
			ray->vert_x = ceilf(data->pl->pl_x);
			ray->vert_y = data->pl->pl_y + \
			((ray->vert_x - data->pl->pl_x) * tan(ray->orient));
		}
		ray->vertical_dist = sqrt(pow(data->pl->pl_x - ray->vert_x, 2) + \
								pow(data->pl->pl_y - ray->vert_y, 2));
	}
	else
	{
		ray->vertical_dist = data->render_dist + 42;
		ray->vert_end = true;
	}
}

void	first_horizontal(t_data *data, t_ray *ray)
{
	if (!(ray->orient == 0 || ray->orient == PI \
		|| ray->orient == (2 * PI)))
	{
		if (ray->orient > PI)
		{
			ray->hori_y = floorf(data->pl->pl_y);
			ray->hori_x = data->pl->pl_x + \
				((data->pl->pl_y - ray->hori_y) / -tan(ray->orient));
		}
		else
		{
			ray->hori_y = ceilf(data->pl->pl_y);
			ray->hori_x = data->pl->pl_x + \
				((ray->hori_y - data->pl->pl_y) / tan(ray->orient));
		}
		ray->horizontal_dist = sqrt(pow(data->pl->pl_x - ray->hori_x, 2) + \
								pow(data->pl->pl_y - ray->hori_y, 2));
	}
	else
	{
		ray->horizontal_dist = data->render_dist + 42;
		ray->hori_end = true;
	}
}

void	horizontal_delta(t_ray *ray)
{
	if (ray->orient > PI)
	{
		ray->h_delta_y = -1;
		ray->h_delta_x = 1 / -tan(ray->orient);
	}
	else
	{
		ray->h_delta_y = 1;
		ray->h_delta_x = 1 / tan(ray->orient);
	}
	ray->h_step_dist = sqrt(pow(ray->hori_x - \
			(ray->hori_x + ray->h_delta_x), 2) \
			+ pow(ray->hori_y - (ray->hori_y + ray->h_delta_y), 2));
}

void	vertical_delta(t_ray *ray)
{
	if (ray->orient < 1.5 * PI && ray->orient > PI / 2)
	{
		ray->v_delta_x = -1;
		ray->v_delta_y = 1 * -tan(ray->orient);
	}
	else
	{
		ray->v_delta_x = 1;
		ray->v_delta_y = 1 * tan(ray->orient);
	}
	ray->v_step_dist = sqrt(pow(ray->vert_x - \
			(ray->vert_x + ray->v_delta_x), 2) \
			+ pow(ray->vert_y - (ray->vert_y + ray->v_delta_y), 2));
}

int	update_ray_dist(t_ray *ray, int flag)
{
	if (ray->hori_end == false && flag == HORI)
	{
		ray->hori_x += ray->h_delta_x;
		ray->hori_y += ray->h_delta_y;
		ray->horizontal_dist += ray->h_step_dist;
		return (0);
	}
	if (ray->vert_end == false && flag == VERT)
	{
		ray->vert_x += ray->v_delta_x;
		ray->vert_y += ray->v_delta_y;
		ray->vertical_dist += ray->v_step_dist;
		return (0);
	}
	return (1);
}
