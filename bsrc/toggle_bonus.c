/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:24:14 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 17:05:52 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_door(t_data *data, float y, float x)
{
	if (y < 0 || x < 0 || y > data->map_y_border || x > data->map_x_border)
		return (1);
	if (data->map[(int)y][(int)x] == '1')
		return (1);
	else if (data->map[(int)y][(int)x] == '2')
		return (2);
	else if (data->map[(int)y][(int)x] == '3')
		return (3);
	else if (data->map[(int)y][(int)x] == '4')
		return (4);
	else if (data->map[(int)y][(int)x] == '5')
		return (5);
	return (0);
}

int	check_toggle(t_data *data, t_pl *pl, float door_y, float door_x)
{
	if ((int)door_y == (int)pl->pl_y && (int)door_x == (int)pl->pl_x)
		return (0);
	if (ft_door(data, door_y, door_x) == 4)
	{
		data->map[(int)door_y][(int)door_x] += 1;
		data->cage++;
		return (victory(data));
	}
	else if (ft_door(data, door_y, door_x) == 5)
	{
		data->map[(int)door_y][(int)door_x] -= 1;
		data->cage--;
		return (1);
	}
	else if (ft_collision(data, door_y, door_x) == 2)
	{
		data->map[(int)door_y][(int)door_x] += 1;
		return (1);
	}
	else if (ft_door(data, door_y, door_x) == 3)
	{
		data->map[(int)door_y][(int)door_x] -= 1;
		return (1);
	}
	return (0);
}

void	toggle_tile(t_data *data, t_pl *pl)
{
	float	door_x;
	float	door_y;
	int		i;

	pl->stp_y = 0.2 * cos(pl->orient - (90 * DG_RD));
	pl->stp_x = 0.2 * sin(pl->orient - (90 * DG_RD));
	i = 0;
	door_x = pl->pl_x;
	door_y = pl->pl_y;
	while (i < 5)
	{
		door_x -= pl->stp_x;
		door_y += pl->stp_y;
		if (check_toggle(data, pl, door_y, door_x) == 1)
			break ;
		i++;
	}
}

void	key_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		toggle_tile(data, data->pl);
}
