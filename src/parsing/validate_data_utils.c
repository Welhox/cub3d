/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:08:01 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/26 11:45:43 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static void	set_player_pos(char c, t_data *data, int y, int x)
{
	if (c == 'N')
		data->player->p_orientation = 270 * DEG_RAD;
	else if (c == 'E')
		data->player->p_orientation = 0;
	else if (c == 'S')
		data->player->p_orientation = 90 * DEG_RAD;
	else if (c == 'W')
		data->player->p_orientation = 180 * DEG_RAD;
	data->player->pl_x = (float)x + 0.5;
	data->player->pl_y = (float)y + 0.5;
}

static int	check_valid_chars(t_data *data, int y, int x)
{
	if (data->map[y][x] != '0' \
	&& data->map[y][x] != 'N' \
	&& data->map[y][x] != 'E' \
	&& data->map[y][x] != 'S' \
	&& data->map[y][x] != 'W' \
	&& data->map[y][x] != ' ' \
	&& data->map[y][x] != '1')
		return (1);
	return (0);
}

static int	check_map(t_data *data, int y, int x, bool *player)
{
	if (data->map[y][x] != '1' && data->map[y][x] != ' ')
	{
		if (pos_check(data, y, x))
			return (1);
		if (data->map[y][x] == 'N' || data->map[y][x] == 'E' \
			|| data->map[y][x] == 'S' || data->map[y][x] == 'W')
		{	
			set_player_pos(data->map[y][x], data, y, x);
			if (*player == true)
				return (1);
			else
				*player = true;
		}
	}
	return (0);
}

int	validate_map(t_data *data)
{
	int		x;
	int		y;
	bool	player;

	player = false;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (check_valid_chars(data, y, x))
				return (1);
			if (check_map(data, y, x, &player))
				return (1);
			x++;
		}
		y++;
	}
	if (player == false)
		return (1);
	return (0);
}
