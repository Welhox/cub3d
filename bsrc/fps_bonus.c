/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:58:36 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 17:25:43 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	get_fps(void *param)
{
	t_data		*data;
	double		frame2;

	data = param;
	frame2 = mlx_get_time();
	data->fm = (frame2 - data->frame);
	data->frame = frame2;
}
