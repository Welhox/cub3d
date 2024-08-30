/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:31:55 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 14:41:55 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sprite_dist(t_data *data, t_sprite *sprite)
{
	float	x;
	float	y;

	x = sprite->x - data->pl->pl_x;
	y = sprite->y - data->pl->pl_y;
	sprite->dist = sqrt(pow(x, 2) + pow(y, 2));
	sprite->angle = atan2(y, x) - data->pl->orient;
	if (sprite->angle < -PI)
        sprite->angle += 2 * PI;
    if (sprite->angle > PI)
        sprite->angle -= 2 * PI;
}

void	sprite_scale(t_data *data, t_sprite *sprite, mlx_image_t *frame)
{
	sprite->scale = data->ray->proj_plane / (sprite->dist * 40);
	sprite->width = sprite->scale * frame->width;
	sprite->height = sprite->scale * frame->height;
}

void ft_swap(int *arr, int a, int b)
{
	int	temp;

	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void	bubble_sort(t_data *data, int *order, float *dist)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (data->s_count - 1))
	{
		j = 0;
		while (j < data->s_count - i - 1)
		{
			if (dist[order[j]] < dist[order[j + 1]])
				ft_swap(order, j, j + 1);
			j++;
		}
	}
}