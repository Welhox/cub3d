/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimirri <clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/21 11:42:13 by casimirri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_params(t_data *data, t_ray *ray)
{
	data->s_height = 1000;
	data->s_width = 1600;
	data->fov = 60;
	data->ms_x = data->s_width / 2.0;
	data->ms_y = data->s_height / 2.0;
	data->left = data->ms_x - (data->ms_x * 0.95);
	data->right = data->ms_y + (data->ms_y * 0.95);
	data->render_dist = 20;
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

	safe_image(data, data->s_width, data->s_height, &data->img->fg_ceiling);//ONLY BONUS
	mlx_image_to_window(data->mlx, data->img->fg_ceiling, 0, 0);//ONLY BONUS
	safe_image(data, data->s_width, data->s_height, &data->img->fg_floor);//ONLY BONUS
	mlx_image_to_window(data->mlx, data->img->fg_floor, 0, 0);//ONLY BONUS
	
	
	
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
	safe_texture(data, &temp, "assets/Door03.png");
	safe_txt_to_img(data, temp, &data->img->door);
	safe_texture(data, &temp, "assets/floor_lava.png");
	safe_txt_to_img(data, temp, &data->img->floor_txt);
	safe_texture(data, &temp, "assets/floor_02.png");
	safe_txt_to_img(data, temp, &data->img->ceil_txt);
}

 void	key_input(mlx_key_data_t keydata, void *param)

{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		toggle_door(data, data->pl);
}
 
void	mlx_main(t_data *data)
{
	t_img	img;

	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	data->img = &img;
	img.mlx = data->mlx;
	if (!data->mlx)
		armageddon(data, "mlx failed to initialise");
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->s_width / 2, data->s_height / 2);
	load_textures(data, &img);
	init_img_text(data->img);
	initial_render(data);
	mlx_key_hook(data->mlx, &key_input, data);
	mlx_cursor_hook(data->mlx, &mouse_callback, data);
	mlx_loop_hook(data->mlx, &keypress, data);
	mlx_loop_hook(data->mlx, &update_mouse, data);
	mlx_loop_hook(data->mlx, ray_main, data);
	mlx_loop(data->mlx);
}


/* 
    //timing for input and FPS counter
    oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
    redraw(); */


/* void get_fps(void *param)
{
	t_data		*data;
	double		frame2;
	
	
	data = param;
	frame2 = 0;
	frame2 = get_time(data);
	data->fps = data->frames / (frame2 - data->frame1);
	data->frames++;
	if (data->frames > 999999999)
	{
		data->frames = 0;
		data->frame1 = frame2;
	}
	//data->frame1 = frame2;
	printf("FPS =  %ld\n", data->fps);
} */