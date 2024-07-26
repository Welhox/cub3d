/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:55 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/26 11:45:35 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	set_map_border(char **temp_data, t_data *data)
{
	int	x;
	int	y;
	int	max;

	max = 0;
	x = 0;
	y = 0;
	while (temp_data[y])
	{
		x = 0;
		while (temp_data[y][x])
			x++;
		if (x > max)
			max = x;
		y++;
	}
	data->map_x_border = max;
	data->map_y_border = y;
	data->map = ft_calloc((y + 2), sizeof(char *)); //calloc checks
	if (!data->map)
		return (-1);
	return (max);
}

static int	map_init(char **temp_data, t_data *data)
{
	int	x;
	int	max;

	x = 0;
	max = set_map_border(temp_data, data);
	if (max == -1)
		return (1);
	while (x <= data->map_y_border)
	{
		data->map[x] = ft_calloc(max + 1, sizeof(char));
		if (!data->map[x])
			return (1);
		x++;
	}
	return (0);
}

int	map_parse(char *map_str, t_data *data)
{
	char	**temp_data;
	int		x;
	int		y;

	y = 0;
	temp_data = ft_split(map_str, '\n');
	ft_nullfree(map_str, 0);
	if (!temp_data)
		return (ret_error("malloc failed"));
	if (map_init(temp_data, data))
		return (ft_nullfree(map_str, 1));
	while (temp_data[y])
	{
		x = 0;
		while (temp_data[y][x])
		{
			data->map[y][x] = temp_data[y][x];
			x++;
		}
		y++;
	}
	ft_arrfree(temp_data);
	return (0);
}