/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:39 by clundber          #+#    #+#             */
/*   Updated: 2024/07/17 11:13:37 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h" 

int main(int ac, char **av)
{
	t_data		data;
	t_ray		ray;
	init_all(&data, &ray);
	parsing(ac, av, &data);
	update_params(&data);
	mlx_main(&data, &ray);
	return (0);
}