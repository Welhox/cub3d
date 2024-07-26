/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:39 by clundber          #+#    #+#             */
/*   Updated: 2024/07/26 16:11:31 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h" 

void	free_images(t_images *img)
{
	if (img->mm)
		mlx_delete_image(img->mlx, img->mm);
	if (img->wall)
		mlx_delete_image(img->mlx, img->wall);
	if (img->mm_floor)
		mlx_delete_image(img->mlx, img->mm_floor);
	if (img->floor)
		mlx_delete_image(img->mlx, img->floor);
	if (img->ceiling)
		mlx_delete_image(img->mlx, img->ceiling);
	if (img->pl)
		mlx_delete_image(img->mlx, img->pl);
}

void	free_textures(t_images *img)
{
	if (img->n_wall)
		mlx_delete_texture(img->n_wall);
	if (img->s_wall)
		mlx_delete_texture(img->s_wall);
	if (img->w_wall)
		mlx_delete_texture(img->w_wall);
	if (img->e_wall)
		mlx_delete_texture(img->e_wall);		
}

//oh-oh, something went wrong, oh well, kill it all and start again ;)
void	armageddon(t_data *data, char *error)
{
	int	i;

	i = 0;
	if (data->mlx)
	{
		free_images(data->images);
		free_textures(data->images);
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	while (i < 4)
	{
		if (data->wall_text[i])
			ft_nullfree(data->wall_text[i], 0);
		i++;
	}
	ft_mapfree(data->map);
	if (error)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(error, 2);
		exit(1);
	}
	printf("Great success!\n");
	exit(0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_ray		ray;
	t_player	player;

	init_all(&data, &ray, &player);
	if (parsing(ac, av, &data) != 0)
		armageddon(&data, NULL);
	update_params(&data, &ray);
	mlx_main(&data);
	armageddon(&data, NULL);
	return (0);
}
