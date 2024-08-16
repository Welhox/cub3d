/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:26:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/16 11:58:05 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_door(t_data *data, float y, float x)
{
	if (y < 0 || x < 0 || y > data->map_y_border || x > data->map_x_border)
		return (1);
	if (data->map[(int)y][(int)x] == '1')
		return (1);
	else if (data->map[(int)y][(int)x] == '2')
		return (2);
	else if (data->map[(int)y][(int)x] == '3')
		return (3);
	return (0);
}

void	toggle_door(t_data *data, t_pl *pl)
{
	float	door_x;
	float	door_y;
	int		i;

	pl->step_y = 0.2 * cos(pl->p_orientation - (90 * DEG_RAD));
	pl->step_x = 0.2 * sin(pl->p_orientation - (90 * DEG_RAD));
	i = 0;
	door_x = pl->pl_x;
	door_y = pl->pl_y;
	while (i < 5)
	{
		door_x -= pl->step_x;
		door_y += pl->step_y;
		if (ft_collision(data, door_y, door_x) == 2)
		{
			data->map[(int)door_y][(int)door_x] = '3';
			break ;
		}
		else if (ft_door(data, door_y, door_x) == 3 && ((int)door_y != (int)pl->pl_y || (int)door_x != (int)pl->pl_x))
		{
			data->map[(int)door_y][(int)door_x] = '2';
			break ;
		}
		i++;
	}
}

void	keypress(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		armageddon(data, NULL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
						|| mlx_is_key_down(data->mlx, MLX_KEY_UP))
		move_pl(data, data->pl, FORWARD);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) \
						|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		move_pl(data, data->pl, BACK);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_pl(data, data->pl, S_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_pl(data, data->pl, S_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		move_pl(data, data->pl, LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		move_pl(data, data->pl, RIGHT);
	//if (mlx_is_key_down(data->mlx, MLX_KEY_E))
	//	toggle_door(data, data->pl);
}

void	mouse_callback(double x, double y, void *param)
{
	t_data	*data;

	data = param;
	data->mouse_x = x;
	data->mouse_y = y;
}

void	update_mouse(void *param)
{
	t_data	*data;
	float	left;
	float	right;
	float	rotation_speed;
	float	sector;

	data = param;
	left = (data->s_width / 2.0) - ((data->s_width / 2.0) * 0.1);
	right = (data->s_width / 2.0) + ((data->s_width / 2.0) * 0.1);
	sector = 0;
	rotation_speed = 0;
	if (data->mouse_x < left && data->mouse_x != 0.0)
	{
		sector = (left - data->mouse_x) / left;
		rotation_speed = sector * 5;
		data->pl->p_orientation -= rotation_speed * DEG_RAD;
		fix_orientation(&data->pl->p_orientation);
	}
	if (data->mouse_x > right && data->mouse_x != 0.0)
	{
		sector = (data->mouse_x - right) / right;
		rotation_speed = sector * 5;
		data->pl->p_orientation += rotation_speed * DEG_RAD;
		fix_orientation(&data->pl->p_orientation);
	}
}

void	fix_orientation(float *orientation)
{
	if (*orientation < 0)
		*orientation += 2 * PI;
	else if (*orientation > 2 * PI)
		*orientation -= 2 * PI;
}
