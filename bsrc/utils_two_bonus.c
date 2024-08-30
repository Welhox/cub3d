/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:47:20 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 17:08:39 by clundber         ###   ########.fr       */
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
