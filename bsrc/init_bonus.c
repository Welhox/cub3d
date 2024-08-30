/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:08:19 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 17:08:39 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	ray->orient = 0;
	ray->distance = 0;
	ray->horizontal_dist = 0;
	ray->vertical_dist = 0;
	ray->data = data;
	ray->corr_dist = 0;
}

void	init_pl(t_data *data, t_pl *pl)
{
	pl->pl_x = 0;
	pl->pl_y = 0;
	pl->orient = 0;
	pl->stp_y = 0;
	pl->stp_x = 0;
	pl->bub_y = 0;
	pl->bub_x = 0;
	data->pl = pl;
	data->ms_x = 0.0;
	data->ms_y = 0.0;
	data->prev_x = 0.0;
	pl->data = data;
	data->fov = 0;
	data->render_dist = 0;
	data->mlx = NULL;
	data->scale = 0;
	data->frame = 0.0;
}

void	init_texture(t_data *data, t_txt *txt)
{
	data->txt = txt;
	data->depth = NULL;
	data->height = NULL;
	data->s_count = 0;
	data->c_frame = 0;
	data->sprites = NULL;
	txt->wall_face = 0;
	txt->wall_x = 0;
	txt->wall_y = 0;
	txt->pos = 0;
	txt->step = 0;
	txt->height = 0;
	txt->hori_door = false;
	txt->vert_door = false;
	txt->door = false;
	txt->hori_cage = false;
	txt->vert_cage = false;
	txt->cage = false;
}

void	init_all(t_data *data, t_ray *ray, t_pl *pl, t_txt *txt)
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
		data->ceil[i] = -1;
	}
	data->floor[3] = 0;
	data->ceil[3] = 0;
	data->s_height = 0;
	data->s_width = 0;
	init_pl(data, pl);
	init_ray(data, ray);
	init_texture(data, txt);
	data->end = false;
	data->cage = 0;
}

void	init_img_text(t_img *img)
{
	img->mm = NULL;
	img->mm_wall = NULL;
	img->mm_floor = NULL;
	img->floor = NULL;
	img->ceil = NULL;
	img->pl = NULL;
	img->ray_grid = NULL;
	img->fg = NULL;
	img->wall_txt[4] = NULL;
	img->sprite = NULL;
	img->fg_ceiling = NULL;
	img->fg_floor = NULL;
}
