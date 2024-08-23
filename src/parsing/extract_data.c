/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:09:12 by tcampbel          #+#    #+#             */
/*   Updated: 2024/08/23 16:52:59 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	all_data_found(t_data *data, char *map_str)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (!data->wall_text[i] || !data->wall_text[3] || data->floor[i] < 0 \
			|| data->ceil[i] < 0 || !map_str)
			return (1);
	}
	return (0);
}

static char	*cpy_map(t_data *data, char *buffer, char *map_str)
{
	char	*ptr;

	ptr = NULL;
	if (!map_str)
		map_str = ft_strdup(buffer);
	else
	{
		ptr = map_str;
		map_str = ft_strjoin(map_str, buffer);
		ft_nullfree(ptr, 1);
	}
	if (!map_str)
	{
		ft_nullfree(buffer, 1);
		armageddon(data, "malloc failed in parsing");
	}
	return (map_str);
}

static char	*gnl_wrapper(int fd, t_data *data, char *buffer, char *map_str)
{
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (check_line(buffer, data) != 0)
		{
			ft_nullfree(buffer, 1);
			ft_nullfree(map_str, 1);
			armageddon(data, "invalid file data");
		}
		if (data->mapstart > 0)
			map_str = cpy_map(data, buffer, map_str);
		ft_nullfree(buffer, 0);
	}
	return (map_str);
}

int	extract_data(char *arg, t_data *data)
{
	char	*buffer;
	int		fd;
	char	*map_str;

	map_str = NULL;
	fd = 0;
	buffer = NULL;
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (ret_error("open failed"));
	map_str = gnl_wrapper(fd, data, buffer, map_str);
	sprite_count(data, map_str);
	if (all_data_found(data, map_str))
		return (ft_nullfree(map_str, 1));
	if (map_parse(map_str, data))
		return (ft_nullfree(map_str, 1));
	return (0);
}
