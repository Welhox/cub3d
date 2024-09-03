/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimirri <clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:22:49 by clundber          #+#    #+#             */
/*   Updated: 2024/09/03 19:55:22 by casimirri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	load_textures(t_data *data, t_img *img)
{
	mlx_texture_t	*temp;

	safe_texture(data, &temp, data->text[0]);
	safe_txt_to_img(data, temp, &img->wall_txt[0]);
	safe_texture(data, &temp, data->text[2]);
	safe_txt_to_img(data, temp, &img->wall_txt[2]);
	safe_texture(data, &temp, data->text[3]);
	safe_txt_to_img(data, temp, &img->wall_txt[3]);
	safe_texture(data, &temp, data->text[1]);
	safe_txt_to_img(data, temp, &img->wall_txt[1]);
	safe_texture(data, &temp, data->text[6]);
	safe_txt_to_img(data, temp, &data->img->door);
	safe_texture(data, &temp, data->text[7]);
	safe_txt_to_img(data, temp, &data->img->cage);
	safe_texture(data, &temp, data->text[4]);
	safe_txt_to_img(data, temp, &data->img->floor_txt);
	safe_texture(data, &temp, data->text[5]);
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

	path[0] = "assets/tile006.png";
	path[1] = "assets/tile007.png";
	path[2] = "assets/tile008.png";
	path[3] = "assets/tile009.png";
	path[4] = "assets/tile010.png";
	path[5] = "assets/tile011.png";
	path[6] = "assets/tile012.png";
	path[7] = "assets/tile013.png";
	path[8] = "assets/tile014.png";
	path[9] = "assets/tile015.png";
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
