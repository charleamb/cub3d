/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:04:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/03 14:00:03 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ftrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, const char *src, int end)
{
	size_t		i;
	size_t		o;

	o = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[o])
	{
		dest[i + o] = src[o];
		o++;
	}
	dest[o + i] = '\0';
	end = 0;
	end = end + 0;
	return (dest);
}

char	*ft_strcopy(char *dest, const char *src, int end)
{
	size_t		o;

	o = 0;
	while (src[o])
	{
		dest[o] = src[o];
		o++;
	}
	dest[o] = '\0';
	end = 0;
	end = end + 0;
	return (dest);
}
