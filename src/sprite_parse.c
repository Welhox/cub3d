/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:01:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/29 16:29:24 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_sprites(t_sprite *sprites, int s_count)
{
	int	i;
	int	j;

	i= -1;
	while (++i < s_count)
	{
		sprites[i].x = 0.0f;
		sprites[i].y = 0.0f;
		sprites[i].dist = 0.0f;
		sprites[i].angle = 0.0f;
		sprites[i].height = 0.0f;
		sprites[i].width = 0.0f;
		j = -1;
		while (++j < 10)
			sprites[i].frame[j] = NULL;
	}
}

void	sprite_count(t_data *data, char *map_str)
{
	int	i;

	i = -1;
	while (map_str[++i])
	{
		if (map_str[i] == '4')
			data->s_count++;
	}
	if (data->s_count > 0)
	{
		data->sprites = malloc(sizeof(t_sprite) * data->s_count);
		if (!data->sprites)
			armageddon(data, "malloc failure");
		init_sprites(data->sprites, data->s_count);
		data->s_count = 0;
	}
}

void	set_sprite_pos(t_data *data, int y, int x)
{
	data->sprites[data->s_count].x = (float)x + 0.5;
	data->sprites[data->s_count].y = (float)y + 0.5;
	data->s_count++;
}