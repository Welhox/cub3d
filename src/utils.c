/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber < clundber@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:04:25 by clundber          #+#    #+#             */
/*   Updated: 2024/07/24 11:36:07 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ret_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

void	ft_nullfree(char *str)
{
	if (str)
	{
		free (str);
		str = NULL;
	}
}

static int	ft_overflow(int neg, const char *str, int len, int i)

{
	if (str[neg] == '-')
		return (-1);
	else
		return (-1);
}

int	ft_atoi_cubd(const char *str)
{
	long int	num;
	int			i;
	int			neg;
	long int	buf;
	int			len;

	i = 0;
	num = 0;
	buf = 0;
	while (ft_isspace(str[i]))
		i++;
	neg = i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	len = i;
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i++] - 48);
		if (buf > num)
			return (ft_overflow(neg, str, len, i));
		buf = num;
	}
	if (i - len > 3)
		return (-1);
	if (str[neg] == '-')
		num *= -1;
	return (num);
}

void	ft_mapfree(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
		// if (i > 0)
		// 	free(array[i + 1]);
		while (i >= 0)
		{
			free (array[i]);
			i--;
		}
		free (array);
		array = NULL;
	}
}


