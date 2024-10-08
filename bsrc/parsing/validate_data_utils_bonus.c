/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:08:01 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 17:05:53 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	pos_check(t_data *data, int y, int x)
{
	if (x == 0 || y == 0)
		return (1);
	if (data->map[y - 1][x] == ' ' || data->map[y - 1][x] == '\0')
		return (1);
	if (data->map[y + 1][x] == ' ' || data->map[y + 1][x] == '\0')
		return (1);
	if (data->map[y][x - 1] == ' ' || data->map[y][x - 1] == '\0')
		return (1);
	if (data->map[y][x + 1] == ' ' || data->map[y][x + 1] == '\0')
		return (1);
	return (0);
}

static void	set_pl_pos(char c, t_data *data, int y, int x)
{
	if (c == 'N')
		data->pl->orient = 270 * DG_RD;
	else if (c == 'E')
		data->pl->orient = 0;
	else if (c == 'S')
		data->pl->orient = 90 * DG_RD;
	else if (c == 'W')
		data->pl->orient = 180 * DG_RD;
	data->pl->pl_x = (float)x + 0.5;
	data->pl->pl_y = (float)y + 0.5;
}

static int	check_valid_chars(t_data *data, int y, int x)
{
	if (data->map[y][x] != '0' \
	&& data->map[y][x] != 'N' \
	&& data->map[y][x] != 'E' \
	&& data->map[y][x] != 'S' \
	&& data->map[y][x] != 'W' \
	&& data->map[y][x] != ' ' \
	&& data->map[y][x] != '1' \
	&& data->map[y][x] != '2' \
	&& data->map[y][x] != '3' \
	&& data->map[y][x] != '4' )
		return (1);
	return (0);
}

static int	check_map(t_data *data, int y, int x, bool *pl)
{
	if (data->map[y][x] != '1' && data->map[y][x] != ' ')
	{
		if (pos_check(data, y, x))
			return (1);
		if (data->map[y][x] == '4')
			set_sprite_pos(data, y, x);
		if (data->map[y][x] == 'N' || data->map[y][x] == 'E' \
			|| data->map[y][x] == 'S' || data->map[y][x] == 'W')
		{
			set_pl_pos(data->map[y][x], data, y, x);
			if (*pl == true)
				return (1);
			else
				*pl = true;
		}
	}
	return (0);
}

int	validate_map(t_data *data)
{
	int		x;
	int		y;
	bool	pl;

	pl = false;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (check_valid_chars(data, y, x))
				return (1);
			if (check_map(data, y, x, &pl))
				return (1);
			x++;
		}
		y++;
	}
	if (pl == false)
		return (1);
	return (0);
}
