/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:29:09 by clundber          #+#    #+#             */
/*   Updated: 2024/02/07 14:30:56 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_arrfree(char **array)

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
