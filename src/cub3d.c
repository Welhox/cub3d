/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:39 by clundber          #+#    #+#             */
/*   Updated: 2024/07/18 16:01:03 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h" 

void	free_images(t_images *img)
{
	if(img->bg)
		mlx_delete_image(img->mlx, img->bg);
	if(img->mm)
		mlx_delete_image(img->mlx, img->mm);	
	if(img->mm_floor)
		mlx_delete_image(img->mlx, img->mm_floor);
	if(img->wall)
		mlx_delete_image(img->mlx, img->wall);
	if(img->pl)
		mlx_delete_image(img->mlx, img->pl);
}

//oh-oh, something went wrong, oh well, kill it all and start again ;)
void	armageddon(t_data *data, char *error)
{
	int	i;

	i = 0;
	if (data->mlx)
	{
		free_images(data->images);
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
		//free mlx textures
	}
	while(i < 4)
	{
		if (data->wall_text[i])
			ft_nullfree(data->wall_text[i]);
		i++;
	}
	ft_arrfree(data->map);
	if(error)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(error, 2);
	}
	exit(1);
	
}

int main(int ac, char **av)
{
	t_data		data;
	t_ray		ray;
	init_all(&data, &ray);
	if (parsing(ac, av, &data) != 0)
		return (1);
	update_params(&data);
	mlx_main(&data, &ray);
	printf("great success!\n");
	return (0);
}