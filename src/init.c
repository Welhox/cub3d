/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:08:19 by clundber          #+#    #+#             */
/*   Updated: 2024/08/07 14:07:54 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray(t_data *data, t_ray *ray)
{
	data->ray = ray;
	ray->hori_x = 0;
	ray->hori_y = 0;
	ray->vert_x = 0;
	ray->vert_y = 0;
	ray->h_delta_x = 0;
	ray->h_delta_y = 0;
	ray->v_delta_x = 0;
	ray->v_delta_y = 0;
	ray->h_step_dist = 0;
	ray->v_step_dist = 0;
	ray->proj_plane = 0;
	ray->ray_orient = 0;
	ray->distance = 0;
	ray->horizontal_dist = 0;
	ray->vertical_dist = 0;
	ray->data = data;
}

void	init_player(t_data *data, t_player *player)
{
	player->pl_x = 0;
	player->pl_y = 0;
	player->p_orientation = 0;
	player->step_y = 0;
	player->step_x = 0;
	player->bub_y = 0;
	player->bub_x = 0;
	data->player = player;
	player->data = data;
}
void	init_texture(t_data *data, t_txt *txt)
{
	data->txt = txt;
	txt->wall_face = 0;
	txt->wall_x = 0;
	txt->wall_y = 0;
	txt->pos = 0;
	txt->step = 0;
	txt->height = 0;
	txt->hori_door = false;
	txt->vert_door = false;	
	txt->door = false;
}

void	init_all(t_data *data, t_ray *ray, t_player *player, t_txt *txt)
{
	int	i;

	i = -1;
	data->mapstart = -1;
	data->map_x_border = 0;
	data->map_y_border = 0;
	data->map = NULL;
	while (++i < 5)
		data->wall_text[i] = NULL;
	i = -1;
	while (++i < 3)
	{
		data->floor[i] = -1;
		data->ceiling[i] = -1;
	}
	data->floor[3] = 0;
	data->ceiling[3] = 0;
	data->s_height = 0;
	data->s_width = 0;
	data->fov = 0;
	data->render_dist = 0;
	data->mlx = NULL;
	data->scale = 0;
	init_player(data, player);
	init_ray(data, ray);
	init_texture(data, txt);
}

void	init_img_text(t_img *img)
{
	img->mm = NULL;
	img->mm_wall = NULL;
	img->mm_floor = NULL;
	img->floor = NULL;
	img->ceiling = NULL;
	img->pl = NULL;
	img->ray_grid = NULL;
	img->fg = NULL;
/*  	img->wall_txt[0] = NULL;
	img->wall_txt[1] = NULL;
	img->wall_txt[2] = NULL;
	img->wall_txt[3] = NULL;*/
	img->wall_txt[4] = NULL;
}
