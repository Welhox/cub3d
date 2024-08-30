/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:42:24 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 14:39:51 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_mm_pl(t_data *data, t_pl *pl)
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
	else if (data->map[(int)y][(int)x] == '5')
		return (5);
	return (0);
}

void	mvt_step(t_data *data, t_pl *pl, bool strafe)
{
	if (strafe == false)
	{
		pl->min_step_y = (SPD * data->fm) *2.5 * cos(pl->orient - (100 * DEG_RAD));
		pl->step_y = (SPD * data->fm) * cos(pl->orient - (90 * DEG_RAD));
		pl->plus_step_y = (SPD * data->fm) *2.5 * cos(pl->orient - (80 * DEG_RAD));
		pl->min_step_x = (SPD * data->fm) *2.5 * sin(pl->orient - (100 * DEG_RAD));
		pl->step_x = (SPD * data->fm) * sin(pl->orient - (90 * DEG_RAD));
		pl->plus_step_x = (SPD * data->fm) *2.5 * sin(pl->orient - (80 * DEG_RAD));
		pl->bub_y = BUBBLE * cos(pl->orient - (90 * DEG_RAD));
		pl->bub_x = BUBBLE * sin(pl->orient - (90 * DEG_RAD));
	}
	else
	{
		pl->min_step_y = (SPD * data->fm) *2.5 * cos(pl->orient - (10 * DEG_RAD));
		pl->step_y = (SPD * data->fm) * cos(pl->orient);
		pl->plus_step_y = (SPD * data->fm) *2.5 * cos(pl->orient + (10 * DEG_RAD));
		pl->min_step_x = (SPD * data->fm) *2.5 * sin(pl->orient - (10 * DEG_RAD));	
		pl->step_x = (SPD * data->fm) * sin(pl->orient);
		pl->plus_step_x = (SPD * data->fm) *2.5 * sin(pl->orient + (10 * DEG_RAD));
		pl->bub_y = BUBBLE * cos(pl->orient);
		pl->bub_x = BUBBLE * sin(pl->orient);
	}
}

void	fwd_or_back(t_data *data, t_pl *pl, t_key key)
{
	mvt_step(data, pl, false);
	if (key == FORWARD)
	{
		if (!ft_collision(data, pl->pl_y + pl->step_y, pl->pl_x - pl->step_x) &&\
		!ft_collision(data, pl->pl_y + pl->min_step_y, pl->pl_x - pl->min_step_x) &&\
		!ft_collision(data, pl->pl_y + pl->plus_step_y, pl->pl_x - pl->plus_step_x) \
		&& !ft_collision(data, pl->pl_y + pl->bub_y, pl->pl_x - pl->bub_x))
		{
			pl->pl_y += pl->step_y;
			pl->pl_x -= pl->step_x;
		}
	}
	if (key == BACK)
	{
		if (!ft_collision(data, pl->pl_y - pl->step_y, pl->pl_x + pl->step_x) &&\
		!ft_collision(data, pl->pl_y - pl->min_step_y, pl->pl_x + pl->min_step_x) && \
		!ft_collision(data, pl->pl_y - pl->plus_step_y, pl->pl_x + pl->plus_step_x)  \
		&& !ft_collision(data, pl->pl_y - pl->bub_y, pl->pl_x + pl->bub_x))
		{
			pl->pl_y -= pl->step_y;
			pl->pl_x += pl->step_x;
		}
	}
}

void	left_or_right(t_data *data, t_pl *pl, t_key key)
{
	mvt_step(data, pl, true);
	if (key == S_LEFT)
	{
		if (!ft_collision(data, pl->pl_y - pl->step_y, pl->pl_x + pl->step_x) &&\
		!ft_collision(data, pl->pl_y - pl->min_step_y, pl->pl_x + pl->min_step_x) &&\
		!ft_collision(data, pl->pl_y - pl->plus_step_y, pl->pl_x + pl->plus_step_x) \
			&& !ft_collision(data, pl->pl_y - pl->bub_y, pl->pl_x + pl->bub_x))
		{
			pl->pl_y -= pl->step_y;
			pl->pl_x += pl->step_x;
		}
	}
	if (key == S_RIGHT)
	{
		if (!ft_collision(data, pl->pl_y + pl->step_y, pl->pl_x - pl->step_x) && \
		!ft_collision(data, pl->pl_y + pl->min_step_y, pl->pl_x - pl->min_step_x) && \
		!ft_collision(data, pl->pl_y + pl->plus_step_y, pl->pl_x - pl->plus_step_x) \
			&& !ft_collision(data, pl->pl_y + pl->bub_y, pl->pl_x - pl->bub_x))
		{
			pl->pl_y += pl->step_y;
			pl->pl_x -= pl->step_x;
		}
	}
}

void	move_pl(t_data *data, t_pl *pl, t_key key)
{
	if (key == FORWARD || key == BACK)
		fwd_or_back(data, pl, key);
	if (key == S_LEFT || key == S_RIGHT)
		left_or_right(data, pl, key);
	if (key == LEFT)
	{
		pl->orient -= ((0.6 * PI) * data->fm);
		fix_orientation(&pl->orient);
	}
	if (key == RIGHT)
	{
		pl->orient += ((0.6 * PI) * data->fm);
		fix_orientation(&pl->orient);
	}
}
