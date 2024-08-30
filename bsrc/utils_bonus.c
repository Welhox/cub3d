/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:04:25 by clundber          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:38 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ret_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

int	ft_nullfree(char *str, int err)
{
	if (str)
	{
		free (str);
		str = NULL;
	}
	if (err)
		return (1);
	return (0);
}

static int	ft_overflow(int num, const char *str, int *len)
{
	long long	buf;

	buf = 0;
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - 48);
		if (buf > num)
			return (-1);
		buf = num;
		str++;
		(*len)++;
	}
	return (num);
}

int	ft_atoi_cubd(const char *str)
{
	long int	num;
	int			neg;
	int			len;

	num = 0;
	len = 0;
	while (ft_isspace(*str))
		str++;
	neg = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	num = ft_overflow(num, str, &len);
	if (len > 3)
		return (-1);
	return (num * neg);
}

void	ft_mapfree(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
		while (i >= 0)
		{
			free (array[i]);
			i--;
		}
		free (array);
		array = NULL;
	}
}
