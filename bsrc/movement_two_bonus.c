/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_two_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:26:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/09/17 11:53:16 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	keypress(void *param)
{
	t_data	*data;

	data = param;
	mlx_get_mouse_pos(data->mlx, &data->ms_x, &data->ms_y);
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
	if (data->mouse_toggle)
	{
		update_mouse(data);
		mlx_set_mouse_pos(data->mlx, data->s_width / 2, data->s_height / 2);
	}
}

void	update_mouse(void *param)
{
	t_data	*data;

	data = param;
	if (data->ms_x < (data->s_width / 2) && data->ms_x >= 0)
	{
		data->pl->orient -= 2.5 * data->fm;
		fix_orientation(&data->pl->orient);
	}
	else if (data->ms_x > (data->s_width / 2) && data->ms_x < data->s_width)
	{
		data->pl->orient += 2.5 * data->fm;
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
