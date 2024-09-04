/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:47:20 by tcampbel          #+#    #+#             */
/*   Updated: 2024/09/04 15:43:51 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	safe_thread(t_data *data, pthread_t *thread, void *func, void *param)
{
	if (param == NULL)
		param = data;
	if (pthread_create(thread, NULL, func, param))
		armageddon(data, "thread creation failed");
}

void	safe_join(t_data *data, pthread_t thread)
{
	if (pthread_join(thread, NULL))
		armageddon(data, "thread failed to join");
}

void	check_door_or_cage(t_txt *txt, t_ray *ray)
{
	if (ray->horizontal_dist < ray->vertical_dist)
	{
		if (txt->hori_door == true)
			txt->door = true;
		else if (txt->hori_cage == true)
			txt->cage = true;
	}
	else
	{
		if (txt->vert_door == true)
			txt->door = true;
		else if (txt->vert_cage == true)
			txt->cage = true;
	}
}

mlx_image_t	*safe_mlx_puts(t_data *data, char *str, int x, int y)
{
	mlx_image_t	*img;

	img = mlx_put_string(data->mlx, str, x, y);
	if (!img)
		armageddon(data, "string image failed to load");
	return (img);
}

char	*safe_itoa(t_data *data, int n)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
		armageddon(data, "malloc failure");
	return (str);
}
