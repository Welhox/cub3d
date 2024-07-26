/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:39:55 by clundber          #+#    #+#             */
/*   Updated: 2024/07/25 17:49:09 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_name(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
		i++;
	if (i <= 4)
		return (1);
	if (ft_strncmp(&str[i - 4], ".cub", 5) != 0)
		return (1);
	return (0);
}

int	validate_data(t_data *data)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	if (data->ceiling[0] < 0 || data->ceiling[1] < 0 || data->ceiling[2] < 0 \
		|| data->floor[0] < 0 || data->floor[1] < 0 || data->floor[2] < 0)
		return (ret_error("invalid floor/ceiling color"));
	while (i < 3)
	{
		fd = open(data->wall_text[i], O_RDONLY);
		if (fd < 0)
			return (ret_error("incorrect textures"));
		else
			close(fd);
		i++;
	}
	if (validate_map(data))
		return (ret_error("incorrect map"));
	return (0);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (argc != 2 || !argv || !argv[1] || !argv[1][0])
		return (ret_error("invalid arguments"));
	if (check_name(argv[1]) != 0)
		return (ret_error("invalid argument name"));
	if (extract_data(argv[1], data) != 0)
		return (ret_error("invalid file data"));
	if (validate_data(data) != 0)
		return (1);
	return (0);
}
