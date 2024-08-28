/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:54:17 by clundber          #+#    #+#             */
/*   Updated: 2024/02/08 17:02:39 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strdup_gnl(const char *s)

{
	int		len;
	char	*dupe;
	int		i;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	dupe = malloc ((len + 1) * sizeof(char));
	if (!dupe)
	{
		s = NULL;
		return (0);
	}
	while (len > 0)
	{
		dupe[i] = s[i];
		i++;
		len--;
	}
	dupe[i] = '\0';
	return (dupe);
}

char	*rd_check(char *buffer, char *temp, int rd)

{
	free (buffer);
	if (rd < 0)
		return (ft_gnlfree(&temp));
	return (temp);
}

size_t	ft_len(const char *s)

{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr_gnl(const char *s, unsigned int start, size_t len)

{
	int		i;
	char	*substr;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_len(s))
		return (ft_strdup_gnl(""));
	if (len > ft_len(s) || len > (ft_len(s) - start))
		len = ft_len(s) - start;
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	while (s[start] && len > 0)
	{
		substr[i++] = s[start++];
		len--;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)

{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc ((ft_len(s1) + ft_len(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}