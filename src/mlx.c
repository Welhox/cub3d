/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/17 15:07:58 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void	update_params(t_data *data)

{
	data->s_height = 1600;
	data->s_width = 1800;
	data->fov = 60;
	data->fov_depth = 8;
	data->scale = get_scale(data);
}

void	keypress(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
/*	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		//move_forward
 	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		//move_backward
	else if (keydata.key == MLX_KEY_LEFT)
		//turn_left
	else if (keydata.key == MLX_KEY_RIGHT)
		//turn_right
	else if (keydata.key == MLX_KEY_A)
		//strafe_left
	else if (keydata.key == MLX_KEY_D)
		//strafe_right */
}

void	mlx_main(t_data *data, t_ray *ray)
{
	t_images	img;

	data->images = &img;
	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	if (!data->mlx)
		exit (1);
	minimap(data, data->images);
	mlx_key_hook(data->mlx, &keypress, data);

	mlx_loop(data->mlx);
}