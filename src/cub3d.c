/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:39 by clundber          #+#    #+#             */
/*   Updated: 2024/07/18 11:11:27 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h" 

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