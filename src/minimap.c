/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:01:31 by clundber          #+#    #+#             */
/*   Updated: 2024/07/26 16:21:20 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mm_render(t_data *data, t_player *player, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, img->mm_wall, \
									data->scale * x, data->scale * y);
			else if (data->map[y][x] == '0')
				mlx_image_to_window(data->mlx, img->mm_floor, \
									data->scale * x, data->scale * y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, img->mm_floor, \
	data->scale * floor(player->pl_x), data->scale * floor(player->pl_y));
}

void	minimap(t_data *data, t_img *img)
{
	float	p_pos_x;
	float	p_pos_y;

	p_pos_x = data->scale * data->player->pl_x - ((data->scale / 5) / 2);
	p_pos_y = data->scale * data->player->pl_y - ((data->scale / 5) / 2);
	//safe_image(data, data->s_width / mms, data->s_height / mms, &img->mm);
	safe_image(data, data->map_x_border * data->scale, data->map_y_border * data->scale, &img->mm);
	safe_image(data, data->scale / mms, data->scale / mms, &img->pl);
	safe_image(data, data->scale - 1, data->scale - 1, &img->mm_wall);
	safe_image(data, data->scale - 1, data->scale - 1, &img->mm_floor);
	safe_image(data, data->s_width / mms, data->s_height / mms, &img->ray_grid);
	color_image(img->mm, make_color(100, 100, 100, 200));
	color_image(img->pl, make_color(255, 0, 0, 255));
	color_image(img->mm_wall, make_color(0, 0, 0, 255));
	color_image(img->mm_floor, make_color(200, 200, 200, 255));
	mlx_image_to_window(data->mlx, img->mm, 0, 0);
	mm_render(data, data->player, img);
	mlx_image_to_window(data->mlx, img->pl, p_pos_x, p_pos_y);
	mlx_image_to_window(data->mlx, img->ray_grid, 0, 0);
}

float	get_scale(t_data *data)
{
	float	height;
	float	width;

	height = 0;
	width = 0;
	height = (data->s_height / data->map_y_border) / 3;
	width = (data->s_width / data->map_x_border) / 3;
	if (height < width)
		return (height);
	else
		return (width);
}
