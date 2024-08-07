/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:42:24 by clundber          #+#    #+#             */
/*   Updated: 2024/08/07 13:57:36 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_mm_player(t_data *data, t_player *pl)
{
	float	scale_x;
	float	scale_y;

	scale_x = data->scale * pl->pl_x - ((data->scale / 5) / 2);
	scale_y = data->scale * pl->pl_y - ((data->scale / 5) / 2);
	data->img->pl->instances[0].x = scale_x;
	data->img->pl->instances[0].y = scale_y;
}

//returns 1 if sq is wall or outside border
int	ft_collision(t_data *data, float y, float x)
{
	if (y < 0 || x < 0 || y > data->map_y_border || x > data->map_x_border)
		return (1);
	if (data->map[(int)y][(int)x] == '1')
		return (1);
	else if (data->map[(int)y][(int)x] == '2')
		return (2);	
	return (0);
}

// void	move_f_or_b(t_data *data, t_key key, )

void	fwd_or_back(t_data *data, t_player *pl, t_key key)
{
	pl->step_y = 0.1 * cos(pl->p_orientation - (90 * DEG_RAD));
	pl->step_x = 0.1 * sin(pl->p_orientation - (90 * DEG_RAD));
	pl->bub_y = BUBBLE * cos(pl->p_orientation - (90 * DEG_RAD));
	pl->bub_x = BUBBLE * sin(pl->p_orientation - (90 * DEG_RAD));
	if (key == FORWARD)
	{
		if (!ft_collision(data, pl->pl_y + pl->step_y, pl->pl_x - pl->step_x) \
		&& !ft_collision(data, pl->pl_y + pl->bub_y, pl->pl_x - pl->bub_x))
		{
			pl->pl_y += pl->step_y;
			pl->pl_x -= pl->step_x;
		}
	}
	if (key == BACK)
	{
		if (!ft_collision(data, pl->pl_y - pl->step_y, pl->pl_x + pl->step_x) \
		&& !ft_collision(data, pl->pl_y - pl->bub_y, pl->pl_x + pl->bub_x))
		{
			pl->pl_y -= pl->step_y;
			pl->pl_x += pl->step_x;
		}
	}
}

void	left_or_right(t_data *data, t_player *pl, t_key key)
{
	pl->step_y = 0.1 * cos(pl->p_orientation);
	pl->step_x = 0.1 * sin(pl->p_orientation);
	pl->bub_y = BUBBLE * cos(pl->p_orientation);
	pl->bub_x = BUBBLE * sin(pl->p_orientation);
	if (key == S_LEFT)
	{
		if (!ft_collision(data, pl->pl_y - pl->step_y, pl->pl_x + pl->step_x) \
			&& !ft_collision(data, pl->pl_y - pl->bub_y, pl->pl_x + pl->bub_x))
		{
			pl->pl_y -= pl->step_y;
			pl->pl_x += pl->step_x;
		}
	}
	if (key == S_RIGHT)
	{
		if (!ft_collision(data, pl->pl_y + pl->step_y, pl->pl_x - pl->step_x) \
			&& !ft_collision(data, pl->pl_y + pl->bub_y, pl->pl_x - pl->bub_x))
		{
			pl->pl_y += pl->step_y;
			pl->pl_x -= pl->step_x;
		}
	}
}

void	move_player(t_data *data, t_player *pl, t_key key)
{
	if (key == FORWARD || key == BACK)
		fwd_or_back(data, pl, key);
	if (key == S_LEFT || key == S_RIGHT)
		left_or_right(data, pl, key);
	if (key == LEFT)
	{
		pl->p_orientation -= 4 * DEG_RAD;
		fix_orientation(&pl->p_orientation);
	}
	if (key == RIGHT)
	{
		pl->p_orientation += 4 * DEG_RAD;
		fix_orientation(&pl->p_orientation);
	}
}
