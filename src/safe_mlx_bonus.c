/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:15:46 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:38 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	safe_txt_to_img(t_data *data, mlx_texture_t *text, mlx_image_t **img)
{
	*img = mlx_texture_to_image(data->mlx, text);
	if (!*img)
		armageddon(data, "texture failed to convert to image");
	mlx_delete_texture(text);
}

void	safe_texture(t_data *data, mlx_texture_t **img, char *path)
{
	*img = mlx_load_png(path);
	if (!*img)
		armageddon(data, "texture failed to load");
}

void	safe_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (y < img->height && x < img->width)
		mlx_put_pixel(img, x, y, color);
}

void	safe_image(t_data *data, uint32_t w, uint32_t h, mlx_image_t **img)
{
	*img = mlx_new_image(data->mlx, w, h);
	if (!*img)
		armageddon(data, "image mallocing failed");
}

void	safe_delete_img(t_data *data, mlx_image_t *img)
{
	if (img)
		mlx_delete_image(data->mlx, img);
}
