/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:42:24 by clundber          #+#    #+#             */
/*   Updated: 2024/09/10 14:54:44 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
		pl->m_stp_y = (SPD * data->fm) * 2.5 * cos(pl->orient - (100 * DG_RD));
		pl->stp_y = (SPD * data->fm) * cos(pl->orient - (90 * DG_RD));
		pl->p_stp_y = (SPD * data->fm) * 2.5 * cos(pl->orient - (80 * DG_RD));
		pl->m_stp_x = (SPD * data->fm) * 2.5 * sin(pl->orient - (100 * DG_RD));
		pl->stp_x = (SPD * data->fm) * sin(pl->orient - (90 * DG_RD));
		pl->p_stp_x = (SPD * data->fm) * 2.5 * sin(pl->orient - (80 * DG_RD));
		pl->bub_y = BUBBLE * cos(pl->orient - (90 * DG_RD));
		pl->bub_x = BUBBLE * sin(pl->orient - (90 * DG_RD));
	}
	else
	{
		pl->m_stp_y = (SPD * data->fm) * 2.5 * cos(pl->orient - (10 * DG_RD));
		pl->stp_y = (SPD * data->fm) * cos(pl->orient);
		pl->p_stp_y = (SPD * data->fm) * 2.5 * cos(pl->orient + (10 * DG_RD));
		pl->m_stp_x = (SPD * data->fm) * 2.5 * sin(pl->orient - (10 * DG_RD));
		pl->stp_x = (SPD * data->fm) * sin(pl->orient);
		pl->p_stp_x = (SPD * data->fm) * 2.5 * sin(pl->orient + (10 * DG_RD));
		pl->bub_y = BUBBLE * cos(pl->orient);
		pl->bub_x = BUBBLE * sin(pl->orient);
	}
}

void	fwd_or_back(t_data *data, t_pl *pl, t_key key)
{
	mvt_step(data, pl, false);
	if (key == FORWARD)
	{
		if (!ft_collision(data, pl->pl_y + pl->stp_y, pl->pl_x - pl->stp_x) \
		&& !ft_collision(data, pl->pl_y + pl->m_stp_y, pl->pl_x - pl->m_stp_x) \
		&& !ft_collision(data, pl->pl_y + pl->p_stp_y, pl->pl_x - pl->p_stp_x) \
		&& !ft_collision(data, pl->pl_y + pl->bub_y, pl->pl_x - pl->bub_x))
		{
			pl->pl_y += pl->stp_y;
			pl->pl_x -= pl->stp_x;
		}
	}
	if (key == BACK)
	{
		if (!ft_collision(data, pl->pl_y - pl->stp_y, pl->pl_x + pl->stp_x) && \
		!ft_collision(data, pl->pl_y - pl->m_stp_y, pl->pl_x + pl->m_stp_x) && \
		!ft_collision(data, pl->pl_y - pl->p_stp_y, pl->pl_x + pl->p_stp_x) \
		&& !ft_collision(data, pl->pl_y - pl->bub_y, pl->pl_x + pl->bub_x))
		{
			pl->pl_y -= pl->stp_y;
			pl->pl_x += pl->stp_x;
		}
	}
}

void	left_or_right(t_data *data, t_pl *pl, t_key key)
{
	mvt_step(data, pl, true);
	if (key == S_LEFT)
	{
		if (!ft_collision(data, pl->pl_y - pl->stp_y, pl->pl_x + pl->stp_x) && \
		!ft_collision(data, pl->pl_y - pl->m_stp_y, pl->pl_x + pl->m_stp_x) && \
		!ft_collision(data, pl->pl_y - pl->p_stp_y, pl->pl_x + pl->p_stp_x) \
			&& !ft_collision(data, pl->pl_y - pl->bub_y, pl->pl_x + pl->bub_x))
		{
			pl->pl_y -= pl->stp_y;
			pl->pl_x += pl->stp_x;
		}
	}
	if (key == S_RIGHT)
	{
		if (!ft_collision(data, pl->pl_y + pl->stp_y, pl->pl_x - pl->stp_x) && \
		!ft_collision(data, pl->pl_y + pl->m_stp_y, pl->pl_x - pl->m_stp_x) && \
		!ft_collision(data, pl->pl_y + pl->p_stp_y, pl->pl_x - pl->p_stp_x) \
			&& !ft_collision(data, pl->pl_y + pl->bub_y, pl->pl_x - pl->bub_x))
		{
			pl->pl_y += pl->stp_y;
			pl->pl_x -= pl->stp_x;
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
		pl->orient -= ((0.8 * PI) * data->fm);
		fix_orientation(&pl->orient);
	}
	if (key == RIGHT)
	{
		pl->orient += ((0.8 * PI) * data->fm);
		fix_orientation(&pl->orient);
	}
}
