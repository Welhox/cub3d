/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:42:24 by clundber          #+#    #+#             */
/*   Updated: 2024/07/18 13:30:29 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void update_mm_player(t_data *data)
{
	float	scale_x;
	float	scale_y;

	scale_x = data->scale * data->player_x - ((data->scale / 5) / 2);
	scale_y = data->scale * data->player_y - ((data->scale / 5) / 2);
	data->images->pl->instances[0].x = scale_x;
	data->images->pl->instances[0].y = scale_y;
}
//returns 1 if char is found
int	ft_collision(t_data *data, float y, float x)
{
	if (y < 0 || x < 0 || y > data->map_y_border || x > data->map_x_border)
		return (1);
	if (data->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	fwd_or_back(t_data *data, t_key key)
{
	float	offset_y;
	float	offset_x;
	float	bubble_y;
	float	bubble_x;
	float	bubble;

	bubble = 0.1;
	offset_y = 0.1 * cos(data->p_orientation - (90 * DEG_RAD));
	offset_x = 0.1 * sin(data->p_orientation - (90 * DEG_RAD));
	bubble_y = (0.1 + bubble) * cos(data->p_orientation - (90 * DEG_RAD));
	bubble_x = (0.1 + bubble) * sin(data->p_orientation - (90 * DEG_RAD));
	if (key == FORWARD)
	{
		if (!ft_collision(data, data->player_y + offset_y, data->player_x - offset_x) && \
			!ft_collision(data, data->player_y + bubble_y, data->player_x - bubble_x))
		{
			data->player_y += offset_y;
			data->player_x -= offset_x;
		}
	}
	if (key == BACK)
	{
		if (!ft_collision(data, data->player_y - offset_y, data->player_x + offset_x)&& \
			!ft_collision(data, data->player_y - bubble_y, data->player_x + bubble_x))
		{
			data->player_y -= offset_y;
			data->player_x += offset_x;
		}
	}
}

void	left_or_right(t_data *data, t_key key)
{
	float	offset_y;
	float	offset_x;
	float	bubble_y;
	float	bubble_x;
	float	bubble;

	bubble = 0.1;
	offset_y = 0.1 * cos(data->p_orientation);
	offset_x = 0.1 * sin(data->p_orientation);
	bubble_y = (0.1 + bubble) * cos(data->p_orientation);
	bubble_x = (0.1 + bubble) * sin(data->p_orientation);


	if (key == S_LEFT)
	{
		if (!ft_collision(data, data->player_y - offset_y, data->player_x + offset_x) && \
			!ft_collision(data, data->player_y - bubble_y, data->player_x + bubble_x))
		{
			data->player_y -= offset_y;
			data->player_x += offset_x;
		}
	}
	if (key == S_RIGHT)
	{
		if (!ft_collision(data, data->player_y + offset_y, data->player_x - offset_x) && \
			!ft_collision(data, data->player_y + bubble_y, data->player_x - bubble_x))
		{
			data->player_y += offset_y;
			data->player_x -= offset_x;
		}
	}
}
void	move_player(t_data *data, t_key key)
{
	if (key == FORWARD || key == BACK)
		fwd_or_back(data, key);
	if (key == S_LEFT || key == S_RIGHT)
		left_or_right(data, key);
	if (key == LEFT)
	{
		data->p_orientation -= 2 * DEG_RAD;
		if (data->p_orientation < 0)
			data->p_orientation += 2 * PI;
	}
	if (key == RIGHT)
	{
		data->p_orientation += 2 * DEG_RAD;
		if (data->p_orientation > (2 * PI))
			data->p_orientation -= 2 * PI;
	}
	update_mm_player(data);
}

