/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:47:20 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/23 11:26:21 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	fl_min(float a, float b)
{
	if (a >= b)
		return (b);
	return (a);
}

float	fl_max(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	safe_thread(t_data *data, pthread_t thread, void *func, void *param)
{
	if (param == NULL)
		param = data;
	if (pthread_create(&thread, NULL, func, param))
		armageddon(data, "thread creation failed");
}

void	safe_join(t_data *data, pthread_t thread)
{
	if (pthread_join(thread, NULL))
		armageddon(data, "thread failed to join");
}