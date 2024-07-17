/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:50:44 by tcampbel          #+#    #+#             */
/*   Updated: 2024/07/17 11:52:51 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int colourise(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	update_params(t_data *data)
{
	data->s_height = 600;
	data->s_width = 800;
	data->fov = 60;
	data->fov_depth = 8;
}

void	mlx_main(t_data *data, t_ray *ray)
{
	t_images	img;

	data->images = &img;
	data->mlx = mlx_init(data->s_width, data->s_height, "Hangover", false);
	if (!data->mlx)
		exit (1);
	data->images->mm = mlx_new_image(data->mlx, data->s_width, data->s_height);
	ft_memset(img.mm->pixels, colourise(255, 0, 0, 100), img.mm->width * img.mm->height * sizeof(int32_t));
	mlx_image_to_window(data->mlx, img.mm, 0, 0);
	mlx_loop(data->mlx);
}