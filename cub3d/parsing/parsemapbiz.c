/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemapbiz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:50:04 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/12 17:54:02 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		freesplit(t_struct *ret)
{
	int i;

	i = 0;
	while (ret->split[i])
	{
		free(ret->split[i]);
		i++;
	}
	free(ret->split);
}

int			startmap(t_struct ret)
{
	int	i;
	int	ok;
	int	go;

	i = 0;
	go = 0;
	ok = 0;
	while (ret.buff[i] == '1' || ret.buff[i] == ' ' || ret.buff[i] == '\t')
	{
		if (ret.buff[i] == '1')
			ok = 1;
		i++;
	}
	go = (ok == 1 && i == ft_strlen(ret.buff)) ? 1 : 0;
	return (go);
}

t_struct	remap(t_struct ret, int fd)
{
	int i;

	get_next_line(fd, &ret.buff);
	while (startmap(ret) == 0)
	{
		i = 0;
		while (ret.buff[i] == ' ')
		{
			if (ret.buff[i + 1] == '1')
				return (ret);
			i++;
		}
		free(ret.buff);
		get_next_line(fd, &ret.buff);
	}
	return (ret);
}

/*
** check  longueur et largeur pour malloc
** ret.count  = ligne et ret.len = longueur
** boucle gnl puis close  pour relancer au meme endroit
*/

void		errormap(t_struct ret)
{
	write(1, "error in map\n", 13);
	freeret(&ret);
	exit(0);
}

t_struct	checklen(t_struct ret, int fd, char *av)
{
	while (ret.buff[0] == '1' || ret.buff[0] == ' ' || ret.buff[0] == '\t')
	{
		ret.count++;
		ret.i = 0;
		while (ret.buff[ret.i])
		{
			ret.i++;
			ret.len = (ret.i > ret.len) ? ret.i : ret.len;
		}
		free(ret.buff);
		ret.end = get_next_line(fd, &ret.buff);
	}
	free(ret.buff);
	if (ret.end != 0)
		ret.ok = 0;
	close(fd);
	fd = open(av, O_RDONLY);
	ret = remap(ret, fd);
	return (ret);
}
