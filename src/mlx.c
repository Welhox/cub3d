/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 15:30:27 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_params(t_data *data, t_ray *ray)
{
	data->s_height = 500.0;
	data->s_width = 800.0;
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
	data->height = malloc(sizeof(int) * (int)data->s_width);
	if (!data->height)
		armageddon(data, "malloc failure");
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

	safe_image(data, data->s_width, data->s_height, &data->img->fg_ceiling);//ONLY BONUS
	mlx_image_to_window(data->mlx, data->img->fg_ceiling, 0, 0);//ONLY BONUS
	safe_image(data, data->s_width, data->s_height, &data->img->fg_floor);//ONLY BONUS
	mlx_image_to_window(data->mlx, data->img->fg_floor, 0, 0);//ONLY BONUS
	
	
	
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
	safe_texture(data, &temp, "assets/steel_cage2.png");
	safe_txt_to_img(data, temp, &data->img->cage);
	safe_texture(data, &temp, "assets/floor_lava.png");
	safe_txt_to_img(data, temp, &data->img->floor_txt);
	safe_texture(data, &temp, "assets/floor_02.png");
	safe_txt_to_img(data, temp, &data->img->ceil_txt);
	safe_texture(data, &temp, "assets/borat.png");
	safe_txt_to_img(data, temp, &data->img->end);
}
void	load_sprites(t_data *data)
{
	int				i;
	int				j;
	mlx_texture_t	*temp;
	char			*path[10];

	path[0] = "assets/tile006.png",
	path[1] = "assets/tile007.png",
	path[2] = "assets/tile008.png",
	path[3] = "assets/tile009.png",
	path[4] = "assets/tile010.png",
	path[5] = "assets/tile011.png",
	path[6] = "assets/tile012.png",
	path[7] = "assets/tile013.png",
	path[8] = "assets/tile014.png",
	path[9] = "assets/tile015.png",
	i = -1;
	while (++i < data->s_count)
	{
		j = -1;
		while (++j < 10)
		{
			safe_texture(data, &temp, path[j]);
			safe_txt_to_img(data, temp, &data->sprites[i].frame[j]);
		}
	}
}

 void	key_input(mlx_key_data_t keydata, void *param)

{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{
		data->input = true;
		toggle_tile(data, data->pl);
	}
}

void	mlx_main(t_data *data)
{
	t_img		img;

	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	data->img = &img;
	img.mlx = data->mlx;
	if (!data->mlx)
		armageddon(data, "mlx failed to initialise");
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->s_width / 2, data->s_height / 2);
	load_textures(data, &img);
	init_img_text(data->img);
	load_sprites(data);
	initial_render(data);
	data->input = false;
	mlx_key_hook(data->mlx, &key_input, data);
	mlx_cursor_hook(data->mlx, &mouse_callback, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_loop(data->mlx);	
}
