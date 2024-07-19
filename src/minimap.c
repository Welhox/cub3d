/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:01:31 by clundber          #+#    #+#             */
/*   Updated: 2024/07/19 16:38:02 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mm_render(t_data *data, t_images *img)
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
				mlx_image_to_window(data->mlx, img->wall, data->scale * x, data->scale * y);	
			else if (data->map[y][x] == '0')
				mlx_image_to_window(data->mlx, img->mm_floor, data->scale * x, data->scale * y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, img->mm_floor, data->scale * floor(data->player_x) , data->scale * floor(data->player_y));

}

void	minimap(t_data *data, t_images *img)
{
	data->images->mm = mlx_new_image(data->mlx, data->s_width, data->s_height);
	if (!data->images->mm)
		armageddon(data, "image mallocing failed");
	data->images->pl = mlx_new_image(data->mlx, data->scale / 5, data->scale / 5);
	if (!data->images->pl)
		armageddon(data, "image mallocing failed");
	data->images->wall = mlx_new_image(data->mlx, data->scale -1, data->scale -1);
	if (!data->images->wall)
		armageddon(data, "image mallocing failed");
	data->images->mm_floor = mlx_new_image(data->mlx, data->scale -1, data->scale -1);
	if (!data->images->mm_floor)
		armageddon(data, "image mallocing failed");
	data->images->ray_grid = mlx_new_image(data->mlx, data->s_width, data->s_height);
	if (!data->images->ray_grid)
		armageddon(data, "image mallocing failed");
	color_image(data->images->mm, make_color(100, 100, 100, 255));	
	color_image(data->images->pl, make_color(255, 0, 0, 255));
	color_image(data->images->wall, make_color(0, 0, 0, 255));
	color_image(data->images->mm_floor, make_color(200, 200, 200, 255));
	mlx_image_to_window(data->mlx, img->mm, 0, 0);
	mm_render(data, img);
	mlx_image_to_window(data->mlx, img->pl, data->scale * data->player_x - ((data->scale / 5) / 2), data->scale * data->player_y - ((data->scale / 5) / 2)); // a bit wrong position for the moment	
	mlx_image_to_window(data->mlx, img->ray_grid, 0, 0);
}

float	get_scale(t_data *data)
{
	float	height;
	float	width;

	height = 0;
	width = 0;
	height = data->s_height / data->map_y_border;
	width = data->s_width / data->map_x_border;
	if (height < width)
		return (height);
	else
		return (width);
}
