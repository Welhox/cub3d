/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_utils_two_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:32:22 by casimirri         #+#    #+#             */
/*   Updated: 2024/09/06 14:39:13 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	ft_ismap(char *line)
{
	while (*line && (*line == ' ' || *line == '1' \
	|| *line == '0' || *line == 'N' || *line == 'S' \
	|| *line == 'E' || *line == 'W' || *line == '2' || *line == '3' \
	|| *line == '4'))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (1);
}

int	check_value(int check)
{
	if (check == 2)
		return (0);
	if (check == 1)
		return (1);
	return (0);
}
