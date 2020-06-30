/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 21:42:44 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/11 15:37:20 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			freeret(t_struct *ret)
{
	int m;

	m = 0;
	(ret->nook == 1) ? free(ret->no) : 0;
	(ret->sook == 1) ? free(ret->so) : 0;
	(ret->eaok == 1) ? free(ret->ea) : 0;
	(ret->weok == 1) ? free(ret->we) : 0;
	(ret->sok == 1) ? free(ret->s) : 0;
	if (ret->m > 0)
	{
		while (ret->map[m] && m < ret->count)
		{
			free(ret->map[m]);
			m++;
		}
		free(ret->map);
	}
	initstrut(*ret);
	return (0);
}

t_struct	mapvalid(t_struct ret)
{
	int		m;
	int		i;
	int		verif;

	m = 0;
	verif = 0;
	while (ret.map[m] && m < ret.count)
	{
		i = 0;
		while (ret.map[m][i] && i < ret.len)
		{
			if (ret.map[m][i] == 'N' || ret.map[m][i] == 'S' ||
					ret.map[m][i] == 'E' || ret.map[m][i] == 'W')
				verif++;
			i++;
		}
		m++;
	}
	if (verif != 1)
		errormap(ret);
	return (ret);
}

int			spa(t_struct ret)
{
	if (ret.buff[ret.i + 1] == ' ' || ret.buff[ret.i + 1] == '\t')
		return (1);
	return (0);
}

t_struct	ftdata(t_struct ret, int fd, char *av)
{
	if (ret.buff[ret.i] == 'S' && spa(ret) == 1)
		return (ftspath(ret));
	if (ret.buff[ret.i] == 'F' && spa(ret) == 1)
		return (ftfloor(ret));
	if (ret.buff[ret.i] == 'C' && spa(ret) == 1)
		return (ftski(ret));
	if (ret.buff[ret.i] == 'R' &&
			(ret.buff[ret.i + 1] == ' ' || ret.buff[ret.i + 1] == '\t'))
		return (ftreso(ret));
	if (ret.buff[ret.i] == 'N' && ret.buff[ret.i + 1] == 'O' &&
			(ret.buff[ret.i + 2] == ' ' || ret.buff[ret.i + 2] == '\t'))
		return (ftnopath(ret));
	if (ret.buff[ret.i] == 'S' && ret.buff[ret.i + 1] == 'O' &&
			(ret.buff[ret.i + 2] == ' ' || ret.buff[ret.i + 2] == '\t'))
		return (ftsopath(ret));
	if (ret.buff[ret.i] == 'W' && ret.buff[ret.i + 1] == 'E' &&
			(ret.buff[ret.i + 2] == ' ' || ret.buff[ret.i + 2] == '\t'))
		return (ftwepath(ret));
	if (ret.buff[ret.i] == 'E' && ret.buff[ret.i + 1] == 'A' &&
			(ret.buff[ret.i + 2] == ' ' || ret.buff[ret.i + 2] == '\t'))
		return (fteapath(ret));
	if (ret.ok == 2 && ret.all == 8)
		return (ftmap(ret, fd, av));
	ret.ok = 0;
	return (ret);
}

t_struct	parse(int fd, char *av, t_struct ret)
{
	while (ret.end == 1 && ret.ok != 0)
	{
		ret.end = get_next_line(fd, &ret.buff);
		if (ret.buff[ret.i] && ret.end == 1)
		{
			while (ret.buff[ret.i] == ' ' || ret.buff[ret.i] == '\t')
				ret.i++;
			ret = ftdata(ret, fd, av);
			free(ret.buff);
		}
		else
			free(ret.buff);
	}
	if (ret.ok == 0)
	{
		write(1, "Error data\n", 12);
		freeret(&ret);
		exit(0);
	}
	ret = mapvalid(ret);
	return (ret);
}
