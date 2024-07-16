/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:39 by clundber          #+#    #+#             */
/*   Updated: 2024/07/16 17:47:05 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h" 

int main(int ac, char **av)
{
	t_data	data;
	t_ray	ray;
	init_all(&data, &ray);
	parsing(ac, av, &data);
	return (0);
}