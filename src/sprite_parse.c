/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:01:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/28 16:14:59 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	sprite_count(t_data *data, char *map_str)
{
	int	i;

	i = -1;
	while (map_str[++i])
	{
		if (map_str[i] == '3')
			data->s_count++;
	}
	if (data->s_count > 0)
	{
		data->sprites = malloc(sizeof(t_sprite) * data->s_count);
		if (!data->sprites)
			armageddon(data, "malloc failure");
		data->s_count = 0;
	}
}

void	set_sprite_pos(t_data *data, int y, int x)
{
	data->sprites[data->s_count].x = (float)x + 0.5;
	data->sprites[data->s_count].y = (float)y + 0.5;
	data->s_count++;
}