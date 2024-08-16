/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:43:17 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/16 16:04:32 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sprite(t_data *data, t_ray *ray)
{
	t_sprite		duck;
	mlx_texture_t	*temp;

	duck.x = 26;
	duck.y = 10;
	safe_texture(data, &temp, "assets/duck1.png");
	safe_txt_to_img(data, temp, &duck.txt);
	float	sprite_x = duck.x - data->pl->pl_x;
	float	sprite_y = duck.y - data->pl->pl_y;

}