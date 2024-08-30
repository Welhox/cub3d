/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:42:24 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 15:38:51 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_collision(t_data *data, float y, float x)
{
	if (y < 0 || x < 0 || y > data->map_y_border || x > data->map_x_border)
		return (1);
	if (data->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	fwd_or_back(t_data *data, t_pl *pl, t_key key)
{
	data->pl->stp_y = 0.1 * cos(pl->p_orientation - (90 * DG_RD));
	data->pl->stp_x = 0.1 * sin(pl->p_orientation - (90 * DG_RD));
	if (key == FORWARD)
	{
		pl->pl_y += pl->stp_y;
		pl->pl_x -= pl->stp_x;
	}
	if (key == BACK)
	{
		pl->pl_y -= pl->stp_y;
		pl->pl_x += pl->stp_x;
	}
}

void	left_or_right(t_data *data, t_pl *pl, t_key key)
{
	data->pl->stp_y = 0.1 * cos(pl->p_orientation);
	data->pl->stp_x = 0.1 * sin(pl->p_orientation);
	if (key == S_LEFT)
	{
		pl->pl_y -= pl->stp_y;
		pl->pl_x += pl->stp_x;
	}
	if (key == S_RIGHT)
	{
		pl->pl_y += pl->stp_y;
		pl->pl_x -= pl->stp_x;
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
		pl->p_orientation -= 4 * DG_RD;
		fix_orientation(&pl->p_orientation);
	}
	if (key == RIGHT)
	{
		pl->p_orientation += 4 * DG_RD;
		fix_orientation(&pl->p_orientation);
	}
}
