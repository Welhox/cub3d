/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimirri <clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:39:55 by clundber          #+#    #+#             */
/*   Updated: 2024/09/03 20:04:25 by casimirri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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
	if (data->ceil[0] < 0 || data->ceil[1] < 0 || data->ceil[2] < 0 \
		|| data->floor[0] < 0 || data->floor[1] < 0 || data->floor[2] < 0)
		return (ret_error("invalid floor/ceil color"));
	while (i < 8)
	{
		fd = open(data->text[i], O_RDONLY);
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
