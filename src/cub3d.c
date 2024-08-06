/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:39 by clundber          #+#    #+#             */
/*   Updated: 2024/08/06 14:48:03 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h" 

void	free_img(t_img *img)
{
	if (img->mm)
		mlx_delete_image(img->mlx, img->mm);
	if (img->mm_wall)
		mlx_delete_image(img->mlx, img->mm_wall);
	if (img->mm_floor)
		mlx_delete_image(img->mlx, img->mm_floor);
	if (img->floor)
		mlx_delete_image(img->mlx, img->floor);
	if (img->ceiling)
		mlx_delete_image(img->mlx, img->ceiling);
	if (img->pl)
		mlx_delete_image(img->mlx, img->pl);
	if (img->wall_txt[0])
		mlx_delete_image(img->mlx, img->wall_txt[0]); //or something else as not in the mlx?
	if (img->wall_txt[1])
		mlx_delete_image(img->mlx, img->wall_txt[1]);
	if (img->wall_txt[2])
		mlx_delete_image(img->mlx, img->wall_txt[2]);
	if (img->wall_txt[3])
		mlx_delete_image(img->mlx, img->wall_txt[3]);
}	

//oh-oh, something went wrong, oh well, kill it all and start again ;)
void	armageddon(t_data *data, char *error)
{
	int	i;

	i = 0;
	if (data->mlx)
	{
		free_img(data->img);
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
	t_txt		txt;

	init_all(&data, &ray, &player, &txt);
	if (parsing(ac, av, &data) != 0)
		armageddon(&data, NULL);
	update_params(&data, &ray);
	mlx_main(&data);
	armageddon(&data, NULL);
	return (0);
}
