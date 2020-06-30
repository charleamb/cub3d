/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyrelease.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:28:29 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/15 17:56:11 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_keyrelease(int keycode, t_all *all)
{
	all->vars->key[keycode] = 0;
	return (0);
}

int		ft_keypress(int keycode, t_all *all)
{
	all->vars->key[keycode] = 1;
	return (0);
}

int		nswespace(char map)
{
	int ret;

	ret = 1;
	if (map == 'N')
		ret = 0;
	else if (map == 'S')
		ret = 0;
	else if (map == 'W')
		ret = 0;
	else if (map == 'E')
		ret = 0;
	else if (map == '0')
		ret = 0;
	return (ret);
}

int		pointcub(char *av)
{
	int i;

	i = ft_strlen(av);
	if (ft_strncmp((av + i - 4), ".cub", i))
		return (-1);
	return (0);
}

void	truefilebf(t_struct *ret)
{
	write(1, "Textures goes wrong\n", 20);
	freeret(ret);
	exit(0);
}
