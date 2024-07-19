/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:39:55 by clundber          #+#    #+#             */
/*   Updated: 2024/07/19 11:41:04 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_isspace(char c)
{
	if ((c == 32 || c >= 9 && c <= 13))
		return (1);
	return (0);
}

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

int	ft_empty(char *line)
{
	while (*line && ((*line >= 9 && *line <= 13) || *line == 32))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (1);
}
// Add doors and shit later
int	ft_ismap(char *line)
{
	while (*line && (*line == ' ' || *line == '1' || *line == '0' || *line == 'N' \
		|| *line == 'S' || *line == 'E' || *line == 'W'))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (1);
}

int	check_colour_value(int *arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (arr[i] > 255 || arr[i] < 0)
			return (i);
	}
	return (0);
}

int	get_color(int *arr, char *str)
{
	str += 2;
	while (ft_isspace(*str) && *str)
		str++;
	arr[0] = ft_atoi_cubd(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str && *str == ',')
		str++;
	while (ft_isspace(*str) && *str)
		str++;
	arr[1] = ft_atoi_cubd(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (str && *str == ',')
		str++;
	while (ft_isspace(*str) && *str)
		str++;
	arr[2] = ft_atoi_cubd(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	arr[3] = 1; //transparency
	if (check_colour_value(arr))
		return (1);
	while (ft_isspace(*str) && *str)
		str++;
	if (*str == '\0' || *str == '\n')
		return (0);
	return (1);
}

char *get_path(char *line)
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


int	check_assets(char *line, t_data *data)
{
	char *elements[5];
	int	i;

	elements[0] = "NO";
	elements[1] = "EA";
	elements[2] = "SO";
	elements[3] = "WE";
	elements[4] = NULL;
	i = -1;
	while (elements[++i])
	{
		if (ft_strncmp(line, elements[i], 2) == 0)
		{	
			if (!data->wall_text[i])
			{
				data->wall_text[i] = get_path(line);
				if (!data->wall_text[i])
					return (1);
				return (0);
			}
		}
	}
	return (0);
}

// need to add malloc checks
int	check_line(char *line, t_data *data)
{
	if (ft_empty(line) == 0)
	{
		if (data->mapstart < 0)
			return (0);
		else
			return (1);
	}
	if (check_assets(line, data) == 1)
	 	return (1);	
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (data->floor[3] == 0)
		{
			if (get_color(data->floor, line) == 1)
				return (1);
		}
		else
			return (1);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (data->ceiling[3] == 0)
		{
			if (get_color(data->ceiling, line) == 1)
				return (1);
		}
		else
			return (1);
	}
	if (ft_ismap(line) == 0)
	{
		if (data->mapstart < 0)
			data->mapstart = 1;
		return (0);
	}
	return (0);
}

int	map_init(char **temp_data, t_data *data)
{
	int	x;
	int	y;
	int	max;

	y = 0;
	max = 0;
	while (temp_data[y])
	{
		x = 0;
		while (temp_data[y][x])
			x++;
		if (x > max)
			max = x;
		y++;
	}
	data->map_x_border = max;
	data->map_y_border = y;
	data->map = ft_calloc((y +2), sizeof(char *)); //calloc checks
	if (!data->map)
		return(1);
	x = 0;
	while (x <= y)
	{
		data->map[x] = ft_calloc(max + 1, sizeof(char));
		if(!data->map[x])
			return(1);
		x++;
	}
	return (0);
}

int	map_parse(char *map_str, t_data *data)
{
	char	**temp_data;
	int		x;
	int		y;

	y = 0;
	temp_data = NULL;
	temp_data = ft_split(map_str, '\n');
	ft_nullfree(map_str);
	if (!temp_data)
		return (ret_error("malloc failed"));
	if (map_init(temp_data, data) != 0)
	{
		ft_nullfree(map_str);
		return(1);
	}	
	while (temp_data[y])
	{
		x = 0;
		while (temp_data[y][x])
		{
			data->map[y][x] = temp_data[y][x];
			x++;
		}
		y++;
	}
	 y = 0;
/* 	while (temp_data[y])
	{
		printf("data: %s\n", temp_data[y]);
		y++;
	}  */
	ft_arrfree(temp_data);
	return (0);
}

int	all_data_found(t_data *data, char *map_str)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if(!data->wall_text[i] || !data->wall_text[3] || data->floor < 0 \
			|| data->ceiling < 0 || !map_str)
			return (1);
	}
	return (0);
}

int	extract_data(char *arg, t_data *data)
{
	char	*buffer;
	int		fd;
	char	*map_str;
	char	*ptr;

	ptr = NULL;
	map_str = NULL;
	fd = 0;
	buffer = NULL;
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return(ret_error("open failed"));
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (check_line(buffer, data) != 0)
		{
			ft_nullfree(buffer);
			ft_nullfree(map_str);
			armageddon(data, "invalid file data");
		}
		if (data->mapstart > 0)
		{
			if (!map_str)
				map_str = ft_strdup(buffer);
			else
			{
				ptr = map_str;
				map_str = ft_strjoin(map_str, buffer);
				ft_nullfree(ptr);
			}
			if (!map_str)
			{
				ft_nullfree(buffer);
				armageddon(data, "malloc failed in parsing");
			}
		}
		ft_nullfree(buffer);
	}
	if (all_data_found(data, map_str) != 0)
	{
		ft_nullfree(map_str);
		return (1);
	}
	if (map_parse(map_str, data) != 0) //check return value
	{
		ft_nullfree(map_str);
		return(1);
	}
	return (0);
}

int	pos_check(t_data *data, int y, int x)
{
	if (x == 0 || y == 0)
		return (1);
	if (data->map[y -1][x] == ' ' || data->map[y -1][x] == '\0')
		return (1);
	if (data->map[y +1][x] == ' ' || data->map[y +1][x] == '\0')
		return (1);
	if (data->map[y][x -1] == ' ' || data->map[y][x -1] == '\0')
		return (1);
	if (data->map[y][x +1] == ' ' || data->map[y][x +1] == '\0')
		return (1);
	return (0);
}

void    set_player_pos(char c, t_data *data, int y, int x)
{
    if (c == 'N')
        data->p_orientation = 270 * DEG_RAD;
    else if (c == 'E')
        data->p_orientation = 0;
    else if (c == 'S')
        data->p_orientation = 90 * DEG_RAD;    
    else if (c == 'W')
		data->p_orientation = 180 * DEG_RAD;
	data->player_x = (float)x + 0.5;
	data->player_y = (float)y + 0.5;       
}

int	validate_map(t_data *data)
{
	int		x;
	int		y;
	bool	player;

	player = false;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if(data->map[y][x] != '0' && data->map[y][x] != 'N' && data->map[y][x] != 'E' \
				&& data->map[y][x] != 'S' && data->map[y][x] != 'W' && data->map[y][x] != ' ' && data->map[y][x] != '1')
				return (1);
			if(data->map[y][x] != '1' && data->map[y][x] != ' ')
			{
				if (pos_check(data, y, x) != 0)
					return (1);
				if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S' || data->map[y][x] == 'W')
				{	
                    set_player_pos(data->map[y][x], data, y, x);
					if (player == true)
						return (1);
					else
						player = true; 
				}
			}
			x++;
		}
		y++;
	}
	if (player == false)
		return (1);
	return (0);
}

int	validate_data(t_data *data)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	if (data->ceiling[0] < 0 || data->ceiling[1] < 0 || data->ceiling[2] < 0 || data->floor[0] < 0 || \
		data->floor[1] < 0 || data->floor[2] < 0) //check if over 255?
		return (ret_error("invalid floor/ceiling color"));
	while (i < 4)
	{
		fd = open(data->wall_text[i], O_RDONLY);
		if (fd < 0)
			return(ret_error("incorrect textures"));
		else
			close(fd);
		i++;
	}
	if (validate_map(data) != 0)
		return(ret_error("incorrect map"));
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
