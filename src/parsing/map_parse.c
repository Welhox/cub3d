/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:55 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/26 14:42:05 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	 trim_spaces(char ***temp_data)
{
	int	y;
	int	x;

	y = 0;
	while((*temp_data)[y])
	{
		x = 0;
		while ((*temp_data)[y][x])
			x++;
		if (x > 0)
			x--;
		while (x > 0 && ft_isspace((*temp_data)[y][x]))
			x--;
		(*temp_data)[y][x + 1] = '\0'; //could be very unsafe, may need more protection
		y++;
	}
}

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
	trim_spaces(&temp_data);
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
