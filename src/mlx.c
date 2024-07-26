/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/26 10:55:50 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void	update_params(t_data *data)

{
	data->s_height = 1080;
	data->s_width = 1280;
	data->fov = 60;
	data->render_dist = 8;
	data->scale = get_scale(data);
	data->ray->proj_plane = (data->s_width / 2) / tan((data->fov / 2) * DEG_RAD);
}

void	keypress(void *param)
{
	t_data *data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
			armageddon(data, NULL);
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

void	initial_render(t_data *data)
{

	data->images->fg = mlx_new_image(data->mlx, data->s_width, data->s_height);
	if (!data->images->fg)
		armageddon(data, "image mallocing failed");
	mlx_image_to_window(data->mlx, data->images->fg, 0, 0);
	minimap(data, data->images);
}

void	mlx_main(t_data *data, t_ray *ray)
{
	t_images	img;

	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	data->images = &img;
	img.mlx = data->mlx;
	if (!data->mlx)
		exit (1);
	initial_render(data);

	mlx_loop_hook(data->mlx, &keypress, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_loop(data->mlx);
	//mlx_delete_image(data->mlx, img.pl);
	//mlx_image_to_window(data->mlx, img.pl, data->scale * data->player_x - ((data->scale / 5) / 2), data->scale * data->player_y - ((data->scale / 5) / 2));
}