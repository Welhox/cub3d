/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/19 16:15:37 by clundber         ###   ########.fr       */
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

void	keypress(void *param)
{
	t_data *data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		{
			printf("Great success!\n");
			armageddon(data, NULL);
		}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_UP))
		move_player(data, FORWARD);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		move_player(data, BACK);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, S_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, S_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		move_player(data, LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		move_player(data, RIGHT);
}

void	mlx_main(t_data *data, t_ray *ray)
{
	t_images	img;

	data->images = &img;
	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	img.mlx = data->mlx;
	if (!data->mlx)
		exit (1);
	minimap(data, data->images);
	mlx_loop_hook(data->mlx, &keypress, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, img.pl);
	mlx_image_to_window(data->mlx, img.pl, data->scale * data->player_x - ((data->scale / 5) / 2), data->scale * data->player_y - ((data->scale / 5) / 2));
}