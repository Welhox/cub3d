/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:44:17 by tcampbel          #+#    #+#             */
/*   Updated: 2024/09/03 11:13:42 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*get_path(char *line)
{
	int		len;

	len = 0;
	while (!ft_isspace(*line) && *line)
		line++;
	while (ft_isspace(*line) && *line)
		line++;
	while (line[len] != '\n' && !ft_isspace(line[len]) && line[len])
		len++;
	return (ft_substr(line, 0, len));
}

static char	*jump_str(char *str)
{
	if (*str == '-')
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	while (ft_isspace(*str) && *str)
		str++;
	if (*str && *str == ',')
		str++;
	while (ft_isspace(*str) && *str)
		str++;
	return (str);
}

static int	check_colour_value(int *arr)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (arr[i] > 255)
			return (1);
	}
	return (0);
}

int	get_color(int *arr, char *str)
{
	str += 2;
	while (ft_isspace(*str) && *str)
		str++;
	arr[0] = ft_atoi_cubd(str);
	str = jump_str(str);
	arr[1] = ft_atoi_cubd(str);
	str = jump_str(str);
	arr[2] = ft_atoi_cubd(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (check_colour_value(arr))
		return (1);
	while (ft_isspace(*str) && *str)
		str++;
	if (*str == '\0' || *str == '\n')
		return (0);
	return (1);
}
