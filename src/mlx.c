/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/22 17:38:34 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_params(t_data *data, t_ray *ray)
{
	data->s_height = 1000.0;
	data->s_width = 1600.0;
	data->fov = 60;
	data->ms_x = data->s_width / 2.0;
	data->ms_y = data->s_height / 2.0;
	data->left = data->ms_x - (data->ms_x * 0.95);
	data->right = data->ms_y + (data->ms_y * 0.95);
	data->render_dist = 20;
	data->scale = get_scale(data);
	ray->proj_plane = (data->s_width / 2) / tan((data->fov / 2) * DEG_RAD);
	data->depth = malloc(sizeof(float) * (int)data->s_width);
	if (!data->depth)
		armageddon(data, "malloc failure");
	data->i= 0;
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
	// safe_image(data, data->s_width, data->s_height, &data->img->sprite);
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
	safe_texture(data, &temp, "assets/Door03.png");
	safe_txt_to_img(data, temp, &data->img->door);
	safe_texture(data, &temp, "assets/floor_lava.png");
	safe_txt_to_img(data, temp, &data->img->floor_txt);
	safe_texture(data, &temp, "assets/floor_02.png");
	safe_txt_to_img(data, temp, &data->img->ceil_txt);
}
void	load_sprites(t_data *data, t_sprite *duck)
{
	int				i;
	mlx_texture_t	*temp;
	char			*path[10] = 
	{ 	"assets/tile006.png",
		"assets/tile007.png",
		"assets/tile008.png",
		"assets/tile009.png",
		"assets/tile010.png",
		"assets/tile011.png",
		"assets/tile012.png",
		"assets/tile013.png",
		"assets/tile014.png",
		"assets/tile015.png"
	};
	i = -1;
	while (++i < 10)
	{
		safe_texture(data, &temp, path[i]);
		safe_txt_to_img(data, temp, &duck->frame[i]);
	}
	duck->c_frame = 0;
	duck->e_time = 0;
	duck->t_frame = 0.1f;
}

 void	key_input(mlx_key_data_t keydata, void *param)

{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		toggle_door(data, data->pl);
	data->input = true;
}
 
void	mlx_main(t_data *data)
{
	t_img		img;
	t_sprite	duck;

	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	data->img = &img;
	data->sprites[0] = &duck;
	img.mlx = data->mlx;
	if (!data->mlx)
		armageddon(data, "mlx failed to initialise");
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->s_width / 2, data->s_height / 2);
	load_textures(data, &img);
	init_img_text(data->img);
	load_sprites(data, &duck);
	initial_render(data);
	data->input = false;
	mlx_key_hook(data->mlx, &key_input, data);
	mlx_cursor_hook(data->mlx, &mouse_callback, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_loop(data->mlx);
}
