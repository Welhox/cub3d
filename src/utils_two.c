/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:47:20 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/20 13:50:04 by tcampbel         ###   ########.fr       */
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
