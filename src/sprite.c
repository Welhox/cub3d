/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:43:17 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/20 13:41:42 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sprite_dist(t_data *data, t_sprite *sprite)
{
	float	x;
	float	y;

	x = sprite->x - data->pl->pl_x;
	y = sprite->y - data->pl->pl_y;
	sprite->dist = sqrt(x * x + y * y);
	sprite->angle = atan2(y, x) - data->pl->p_orientation;
	  if (sprite->angle < -PI)
        sprite->angle += 2 * PI;
    if (sprite->angle > PI)
        sprite->angle -= 2 * PI;
}

void	sprite_scale(t_data *data, t_sprite *sprite)
{
	sprite->scale = data->ray->proj_plane / (sprite->dist * 100);
	sprite->width = sprite->scale * sprite->txt->width;
	sprite->height = sprite->scale * sprite->txt->height;
}

void	render_sprite(t_data *data, t_sprite *sprite, t_ray *ray)
{
	float	sp_x;
	int		x;
	int		y;
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
	float	sp_txt_x;
	float	sp_txt_y;

	sprite_dist(data, sprite);
	sprite_scale(data, sprite);
	if (sprite->angle < -PI / 2 || sprite->angle > PI / 2) 
        return;
	sp_x = (data->s_width / 2) + (tan(sprite->angle) * ray->proj_plane);
	start_x = sp_x - (sprite->width / 2);
	end_x = sp_x + (sprite->width / 2);
	start_y = (data->s_height / 2) - (sprite->height / 2);
	end_y = (data->s_height / 2) + (sprite->height / 2);
	x = start_x;
	while (x < end_x)
	{
		if (x >= 0 && x < data->s_width && sprite->dist < data->depth[x])
		{
			y = start_y;
			while (y < end_y)
			{
				if (y >= 0 && y < data->s_height)
				{
					sp_txt_x = ((x - start_x) / sprite->width) * sprite->txt->width;
					sp_txt_y = ((y - start_y) / sprite->height) * sprite->txt->height;
					int	colour = get_txt_color(sprite->txt, sp_txt_x, sp_txt_y, data->txt->shade);
					int	alpha = (colour >> 24) & 0xFF;
					if (alpha != 0)
						safe_pixel(data->img->fg, x, y, colour);
				}
				y++;
			}
		}
		x++;
	}
}

void	sprite(t_data *data, t_ray *ray)
{
	t_sprite		duck;
	mlx_texture_t	*temp;

	duck.x = 26.5;
	duck.y = 10.5;
	safe_texture(data, &temp, "assets/duck1.png");
	safe_txt_to_img(data, temp, &duck.txt);
	render_sprite(data, &duck, ray);
}