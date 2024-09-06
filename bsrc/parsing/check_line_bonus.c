/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:41:18 by tcampbel          #+#    #+#             */
/*   Updated: 2024/09/06 14:39:01 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	ft_empty(char *line)
{
	while (*line && ((*line >= 9 && *line <= 13) || *line == 32))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (1);
}

static void	set_elements(char **elements)
{
	elements[0] = "NO";
	elements[1] = "EA";
	elements[2] = "SO";
	elements[3] = "WE";
	elements[4] = "BF";
	elements[5] = "BC";
	elements[6] = "DO";
	elements[7] = "BS";
	elements[8] = NULL;
}

static int	check_assets(char *line, t_data *data)
{
	char	*elements[9];
	int		i;

	set_elements(elements);
	i = -1;
	while (elements[++i])
	{
		if (ft_strncmp(line, elements[i], 2) == 0)
		{
			if (!data->text[i])
			{
				data->text[i] = get_path(line);
				if (!data->text[i])
					return (1);
				return (2);
			}
			else
				return (1);
		}
	}
	return (0);
}

static int	check_color(char *line, t_data *data)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (data->floor[0] == -1)
		{
			if (get_color(data->floor, line) == 1)
				return (1);
			return (2);
		}
		else
			return (1);
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		if (data->ceil[0] == -1)
		{
			if (get_color(data->ceil, line) == 1)
				return (1);
			return (2);
		}
		else
			return (1);
	}
	return (0);
}

int	check_line(char *line, t_data *data)
{
	int	check;

	check = 0;
	if (ft_empty(line) == 0)
	{
		if (data->mapstart < 0)
			return (0);
		else
			return (1);
	}
	check = check_assets(line, data);
	if (check == 2 || check == 1)
		return (check_value(check));
	check = check_color(line, data);
	if (check == 2 || check == 1)
		return (check_value(check));
	if (ft_ismap(line) == 0)
	{
		if (data->mapstart < 0)
			data->mapstart = 1;
		return (0);
	}
	return (1);
}
