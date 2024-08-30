/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:43:17 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:38 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sprite_pixel(t_data *data, t_sprite *sprite, int x, int y)
{
	float	t_x;
	float	t_y;
	int		colour;
	int		alpha;
	int		i;

	i = data->c_frame;
	t_x = ((x - sprite->start[X]) / sprite->width) * sprite->frame[i]->width;
	t_y = ((y - sprite->start[Y]) / sprite->height) * sprite->frame[i]->height;
	colour = get_txt_color(sprite->frame[i], t_x, t_y, data->txt->shade);
	alpha = (colour >> 24) & 0xFF;
	if (alpha != 0)
		safe_pixel(data->img->sprite, x, y, colour);
}

void	paint_sprite(t_data *data, t_sprite *sprite)
{
	int	x;
	int	y;

	x = sprite->start[X];
	while (x < sprite->end[X])
	{
		if (x >= 0 && x < data->s_width)
		{
			y = sprite->start[Y];
			if (sprite->dist < data->depth[x])
			{
				while (y < sprite->end[Y])
				{
					if (y >= 0 && y < data->s_height)
						sprite_pixel(data, sprite, x, y);
					y++;
				}
			}
		}
		x++;
	}
}

void	render_sprite(t_data *data, t_sprite *sprite, t_ray *ray)
{
	float	center_x;
	float	sp_orient;

	sprite_dist(data, sprite);
	sprite_scale(data, sprite, sprite->frame[data->c_frame]);
	sp_orient = (tan(sprite->angle) * ray->proj_plane);
	if (sprite->angle < (-PI / 2) || sprite->angle > (PI / 2))
		return ;
	center_x = (data->s_width / 2) + sp_orient;
	if (center_x < 0 || center_x > data->s_width)
		return ;
	sprite->start[X] = center_x - (sprite->width / 2);
	sprite->end[X] = center_x + (sprite->width / 2);
	sprite->start[Y] = (data->s_height / 2) - (sprite->height / 2);
	sprite->end[Y] = (data->s_height / 2) + (sprite->height / 2);
	paint_sprite(data, sprite);
}

int	*sort_sprites(t_data *data)
{
	int		*sprite_order;
	float	*sprite_dist;
	int		i;

	i = -1;
	sprite_order = ft_calloc(sizeof(int), data->s_count + 1);
	sprite_dist = ft_calloc(sizeof(float), data->s_count + 1);
	if (!sprite_order || !sprite_dist)
		armageddon(data, "malloc failure");
	while (++i < data->s_count)
	{
		sprite_order[i] = i;
		sprite_dist[i] = data->sprites[i].dist;
	}
	bubble_sort(data, sprite_order, sprite_dist);
	free(sprite_dist);
	return (sprite_order);
}

void	sprite(void *arg)
{	
	int		i;
	int		index;
	int		*order;
	t_data	*data;

	data = arg;
	i = -1;
	order = sort_sprites(data);
	while (++i < data->s_count)
	{
		index = order[i];
		render_sprite(data, &data->sprites[index], data->ray);
	}
	mlx_image_to_window(data->mlx, data->img->sprite, 0, 0);
	mlx_set_instance_depth(data->img->sprite->instances, 5);
	data->c_frame = (data->c_frame + 1) % 10;
	free(order);
}
