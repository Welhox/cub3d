/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:00 by clundber          #+#    #+#             */
/*   Updated: 2024/07/24 11:36:10 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	color_image(mlx_image_t *image, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}	
}

int 	make_color(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	safe_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (y < img->height && x < img->width)
		mlx_put_pixel(img, x, y, color);
}
