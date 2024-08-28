/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:00 by clundber          #+#    #+#             */
/*   Updated: 2024/08/28 11:54:33 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	color_image(mlx_image_t *image, int color)
{
	uint32_t	x;
	uint32_t	y;

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

int	make_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//gives back the color of the pixel
int	get_txt_color(mlx_image_t *img, int x, int y, float shade)
{
	int		color;
	int		x_offset;
	int		y_offset;
	int		i;
	uint8_t	*txt;

	color = 0;
	x_offset = 4;
	y_offset = 4 * img->width;
	i = (x * x_offset) + (y * y_offset);
	txt = img->pixels;
	if (x >= 0 && x <= y_offset && y >= 0 && y < (int)img->height)
		color = make_color(txt[i] * shade, txt[i + 1] * shade, \
							txt[i + 2] * shade, txt[i + 3]);
	return (color);
}

mlx_image_t	*use_txt(t_data *data)
{
	return (data->img->wall_txt[data->txt->wall_face]);
}
