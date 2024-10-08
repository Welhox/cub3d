/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:08:19 by clundber          #+#    #+#             */
/*   Updated: 2024/09/06 11:35:22 by tcampbel         ###   ########.fr       */
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
	pl->p_orientation = 0;
	pl->stp_y = 0;
	pl->stp_x = 0;
	data->pl = pl;
	pl->data = data;
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
	data->fov = 0;
	data->render_dist = 0;
	data->mlx = NULL;
	init_pl(data, pl);
	init_ray(data, ray);
	init_texture(data, txt);
}

void	init_img_text(t_img *img)
{
	img->floor = NULL;
	img->ceil = NULL;
	img->fg = NULL;
	img->wall_txt[4] = NULL;
}
