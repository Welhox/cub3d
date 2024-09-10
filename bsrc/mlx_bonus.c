/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/09/10 14:50:54 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	update_params(t_data *data, t_ray *ray)
{
	data->s_height = 1000.0;
	data->s_width = 1600.0;
	data->fov = 60;
	data->ms_x = data->s_width / 2.0;
	data->ms_y = data->s_height / 2.0;
	data->render_dist = 20;
	data->scale = get_scale(data);
	ray->proj_plane = (data->s_width / 2) / tan((data->fov / 2) * DG_RD);
	data->depth = malloc(sizeof(float) * (int)data->s_width);
	if (!data->depth)
		armageddon(data, "malloc failure");
	data->height = malloc(sizeof(int) * (int)data->s_width);
	if (!data->height)
		armageddon(data, "malloc failure");
}

void	render_score(t_data *data, t_img *img)
{
	data->total_sprites = safe_itoa(data, data->s_count);
	img->counter = safe_mlx_puts(data, "0", data->s_width - 250, \
					data->s_height - 150);
	img->slash = safe_mlx_puts(data, "/", data->s_width - 200, \
					data->s_height - 150);
	img->total = safe_mlx_puts(data, data->total_sprites, \
							data->s_width - 150, data->s_height - 150);
	mlx_resize_image(img->slash, 50, 50);
	mlx_resize_image(img->total, 50, 50);
	mlx_resize_image(img->counter, 50, 50);
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
	safe_image(data, data->s_width, data->s_height, &data->img->fg_ceiling);
	mlx_image_to_window(data->mlx, data->img->fg_ceiling, 0, 0);
	safe_image(data, data->s_width, data->s_height, &data->img->fg_floor);
	mlx_image_to_window(data->mlx, data->img->fg_floor, 0, 0);
	minimap(data, data->img);
	render_score(data, data->img);
}

void	termination(void *param)
{
	t_data	*data;

	data = param;
	armageddon(data, NULL);
}

void	mlx_main(t_data *data)
{
	t_img		img;

	data->mlx = mlx_init(data->s_width, data->s_height, "Cub3 the ducks", false);
	data->img = &img;
	img.mlx = data->mlx;
	if (!data->mlx)
		armageddon(data, "mlx failed to initialise");
	data->mouse_toggle = 1;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->s_width / 2, data->s_height / 2);
	load_textures(data, &img);
	init_img_text(data->img);
	load_sprites(data);
	initial_render(data);
	mlx_key_hook(data->mlx, &key_input, data);
	mlx_mouse_hook(data->mlx, &mouse_input, data);
	mlx_loop_hook(data->mlx, &keypress, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_close_hook(data->mlx, &termination, data);
	mlx_loop(data->mlx);
}
