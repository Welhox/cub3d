/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/12 13:35:17 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_params(t_data *data, t_ray *ray)
{
	data->s_height = 600;
	data->s_width = 800;
	data->fov = 60;
	data->render_dist = 30;
	data->scale = get_scale(data);
	ray->proj_plane = (data->s_width / 2) / tan((data->fov / 2) * DEG_RAD);
}

void	initial_render(t_data *data)
{
	int	ceil;
	int	floor;

	ceil = make_color(data->ceil[0], data->ceil[1], data->ceil[2], 255);
	floor = make_color(data->floor[0], data->floor[1], data->floor[2], 255);
	safe_image(data, data->s_width, data->s_height / 2, &data->img->floor);
	safe_image(data, data->s_width, data->s_height / 2, &data->img->ceil);
	color_image(data->img->ceil, ceil);
	color_image(data->img->floor, floor);
	mlx_image_to_window(data->mlx, data->img->ceil, 0, 0);
	mlx_image_to_window(data->mlx, data->img->floor, 0, data->s_height / 2);
	safe_image(data, data->s_width, data->s_height, &data->img->fg);
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);
	minimap(data, data->img);
}

void	load_textures(t_data *data, t_img *img)
{
	mlx_texture_t	*temp;

	safe_texture(data, &temp, data->wall_text[0]);
	safe_txt_to_img(data, temp, &img->wall_txt[0]);
	safe_texture(data, &temp, data->wall_text[2]);
	safe_txt_to_img(data, temp, &img->wall_txt[2]);
	safe_texture(data, &temp, data->wall_text[3]);
	safe_txt_to_img(data, temp, &img->wall_txt[3]);
	safe_texture(data, &temp, data->wall_text[1]);
	safe_txt_to_img(data, temp, &img->wall_txt[1]);
	safe_texture(data, &temp, "assets/512x512/Wood/Wood_15-512x512.png");
	safe_txt_to_img(data, temp, &data->img->door);
	safe_texture(data, &temp, "assets/BRICK_3B.PNG");
	safe_txt_to_img(data, temp, &data->img->floor_txt);
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
	mlx_cursor_hook(data->mlx, &mouse_callback, data);
	mlx_loop_hook(data->mlx, &keypress, data);
	mlx_loop_hook(data->mlx, &update_mouse, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_loop(data->mlx);
}
