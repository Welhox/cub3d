/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimirri <casimirri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/26 23:16:33 by casimirri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_params(t_data *data, t_ray *ray)

{
	data->s_height = 1080;
	data->s_width = 1920;
	data->fov = 60;
	data->render_dist = 30;
	data->scale = get_scale(data);
	ray->proj_plane = (data->s_width / 2) / tan((data->fov / 2) * DEG_RAD);
}

void	keypress(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		armageddon(data, NULL);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) \
						|| mlx_is_key_down(data->mlx, MLX_KEY_UP))
		move_player(data, data->player, FORWARD);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) \
						|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		move_player(data, data->player, BACK);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, data->player, S_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, data->player, S_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		move_player(data, data->player, LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		move_player(data, data->player, RIGHT);
}

void	initial_render(t_data *data)
{
	int	ceil;
	int	floor;

	ceil = make_color(data->ceiling[0], data->ceiling[1], data->ceiling[2], 255);
	floor = make_color(data->floor[0], data->floor[1], data->floor[2], 255);
	safe_image(data, data->s_width, data->s_height / 2, &data->img->floor);
	safe_image(data, data->s_width, data->s_height / 2, &data->img->ceiling);
	color_image(data->img->ceiling, ceil);
	color_image(data->img->floor, floor);
	mlx_image_to_window(data->mlx, data->img->ceiling, 0, 0);
	mlx_image_to_window(data->mlx, data->img->floor, 0, data->s_height / 2);

	safe_image(data, data->s_width, data->s_height, &data->img->fg);
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
	minimap(data, data->img);
}

void	load_textures(t_data *data, t_img *img)
{
	safe_texture(data, &img->n_wall, data->wall_text[0]);
	safe_text_to_image(data, img->n_wall, &img->wall_n);
	safe_texture(data, &img->s_wall, data->wall_text[2]);
	safe_text_to_image(data, img->s_wall, &img->wall_s);
	safe_texture(data, &img->w_wall, data->wall_text[3]);
	safe_text_to_image(data, img->w_wall, &img->wall_w);
	safe_texture(data, &img->e_wall, data->wall_text[1]);
	safe_text_to_image(data, img->e_wall, &img->wall_e);
}

void	mlx_main(t_data *data)
{
	t_img	img;

	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	data->img = &img;
	img.mlx = data->mlx;
	if (!data->mlx)
		armageddon(data, "mlx failed to initialise");
	load_textures(data, &img);
	init_img_text(data->img);	
	initial_render(data);
	mlx_loop_hook(data->mlx, &keypress, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_loop(data->mlx);
}
