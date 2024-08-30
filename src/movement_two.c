/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:26:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 15:32:50 by clundber         ###   ########.fr       */
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
	else if (data->map[(int)y][(int)x] == '4')
		return (4);
	else if (data->map[(int)y][(int)x] == '5')
		return (5);
	return (0);
}

void	victory(t_data *data)
{
	mlx_resize_image(data->img->end, data->s_width, data->s_height);
	mlx_image_to_window(data->mlx, data->img->end, 0, 0);
	mlx_set_instance_depth(data->img->end->instances, 400);
}

int		check_toggle(t_data *data, t_pl *pl, float door_y, float door_x)
{
	if ((int)door_y == (int)pl->pl_y && (int)door_x == (int)pl->pl_x)
		return (0);
	if (ft_door(data, door_y, door_x) == 4)
	{
		data->map[(int)door_y][(int)door_x] += 1;
		data->cage++;
		if (data->cage == data->s_count)
			victory(data);
		return (1);
	}
	else if (ft_door(data, door_y, door_x) == 5)
	{
		data->map[(int)door_y][(int)door_x] -= 1;
		data->cage--;
		return (1);
	}
	else if (ft_collision(data, door_y, door_x) == 2)
	{
		data->map[(int)door_y][(int)door_x] += 1;
		return (1);
	}
	else if (ft_door(data, door_y, door_x) == 3)
	{
		data->map[(int)door_y][(int)door_x] -= 1;
		return (1);
	}
	return (0);
}

void	toggle_tile(t_data *data, t_pl *pl)
{
	float	door_x;
	float	door_y;
	int		i;

	pl->step_y = 0.2 * cos(pl->orient - (90 * DEG_RAD));
	pl->step_x = 0.2 * sin(pl->orient - (90 * DEG_RAD));
	i = 0;
	door_x = pl->pl_x;
	door_y = pl->pl_y;
	while (i < 5)
	{
		door_x -= pl->step_x;
		door_y += pl->step_y;
		if (check_toggle(data, pl, door_y, door_x) == 1)
			break ;
/* 		if ((ft_collision(data, door_y, door_x) == 2 || ft_door(data, door_y, door_x) == 4) && ((int)door_y != (int)pl->pl_y || (int)door_x != (int)pl->pl_x))
		{
			data->map[(int)door_y][(int)door_x] += 1;
			break ;
		}
		else if ((ft_door(data, door_y, door_x) == 3 || ft_door(data, door_y, door_x) == 5) && ((int)door_y != (int)pl->pl_y || (int)door_x != (int)pl->pl_x))
		{
			data->map[(int)door_y][(int)door_x] -= 1;
			break ;
		} */
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
	update_mouse(data);	
}

void	mouse_callback(double x, double y, void *param)
{
	t_data	*data;

	data = param;
	data->ms_x = x;
	data->ms_y = y;
}

void	update_mouse(void *param)
{
	t_data	*data;
	float	offset;

	data = param;
	offset = data->ms_x - data->prev_x;
	data->prev_x = data->ms_x;
	if ((data->ms_x != (data->s_width / 2) && \
			data->ms_y != (data->s_height / 2))\
			&& (data->ms_x > data->left && data->ms_x < data->right))
	{
		data->pl->orient += (offset * 0.15) * DEG_RAD;
		fix_orientation(&data->pl->orient);
	}
	if (data->ms_x <= data->left)
	{	
		data->pl->orient -= ((0.9 * PI) * data->fm);
		fix_orientation(&data->pl->orient);
	}
	if (data->ms_x >= data->right)
	{
		data->pl->orient += ((0.9 * PI) * data->fm);
		fix_orientation(&data->pl->orient);	
	}
}

void	fix_orientation(float *orientation)
{
	if (*orientation < 0)
		*orientation += 2 * PI;
	else if (*orientation >= 2 * PI)
		*orientation -= 2 * PI;
}
