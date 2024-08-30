/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:58:36 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:38 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_fps(void *param)
{
	t_data		*data;
	double		frame2;

	data = param;
	frame2 = mlx_get_time();
	data->fm = (frame2 - data->frame);
	data->frame = frame2;
}
