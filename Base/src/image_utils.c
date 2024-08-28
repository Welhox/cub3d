/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:00 by clundber          #+#    #+#             */
/*   Updated: 2024/08/28 15:49:34 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	color_image(t_mlx_img *image, int color)
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
int	get_txt_color(t_mlx_img *img, int x, int y, float shade)
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

t_mlx_img	*use_txt(t_data *data)
{
	return (data->img->wall_txt[data->txt->wall_face]);
}

void	refresh_img(t_data *data, t_img *img)
{
	mlx_delete_image(data->mlx, img->fg);
	safe_image(data, data->s_width, data->s_height, &img->fg);
}
