/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_two_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:26:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:38 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
			data->ms_y != (data->s_height / 2)) \
			&& (data->ms_x > data->left && data->ms_x < data->right))
	{
		data->pl->orient += (offset * 0.15) * DG_RD;
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
