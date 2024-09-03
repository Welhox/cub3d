/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_utils_two_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casimirri <clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:32:22 by casimirri         #+#    #+#             */
/*   Updated: 2024/09/03 20:36:54 by casimirri        ###   ########.fr       */
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
