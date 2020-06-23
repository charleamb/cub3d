/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:55:40 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/15 13:14:41 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** fonction recuper de path
** ret.i + 2 pour passer la lettre et potentiel espace
** ret.all++ pour comptabiliser la les donnes recuperer
*/

t_struct	ftnopath(t_struct ret)
{
	if (ret.nook == 1)
	{
		ret.ok = 0;
		write(1, "too much NO\n", 12);
		return (ret);
	}
	ret.nook = 1;
	ret.i = ret.i + 2;
	while (ret.buff[ret.i] == ' ' || ret.buff[ret.i] == '\t')
		ret.i++;
	ret.no = ft_strdup(ret.buff + ret.i);
	if (open(ret.no, O_RDONLY) == -1)
	{
		write(1, "Dumb no path\n", 13);
		ret.ok = 0;
	}
	ret.i = 0;
	ret.all++;
	return (ret);
}

t_struct	ftsopath(t_struct ret)
{
	if (ret.sook == 1)
	{
		ret.ok = 0;
		write(1, "too much SO\n", 12);
		return (ret);
	}
	ret.sook = 1;
	ret.i = ret.i + 2;
	while (ret.buff[ret.i] == ' ' || ret.buff[ret.i] == '\t')
		ret.i++;
	ret.so = ft_strdup(ret.buff + ret.i);
	if (open(ret.so, O_RDONLY) == -1)
	{
		write(1, "Dumb so path\n", 13);
		ret.ok = 0;
	}
	ret.i = 0;
	ret.all++;
	return (ret);
}

t_struct	fteapath(t_struct ret)
{
	if (ret.eaok == 1)
	{
		ret.ok = 0;
		write(1, "too much EA\n", 12);
		return (ret);
	}
	ret.eaok = 1;
	ret.i = ret.i + 2;
	while (ret.buff[ret.i] == ' ' || ret.buff[ret.i] == '\t')
		ret.i++;
	ret.ea = ft_strdup(ret.buff + ret.i);
	if (open(ret.ea, O_RDONLY) == -1)
	{
		write(1, "Dumb ea path\n", 13);
		ret.ok = 0;
	}
	ret.i = 0;
	ret.all++;
	return (ret);
}

t_struct	ftwepath(t_struct ret)
{
	if (ret.weok == 1)
	{
		ret.ok = 0;
		write(1, "too much WE\n", 12);
		return (ret);
	}
	ret.weok = 1;
	ret.i = ret.i + 2;
	while (ret.buff[ret.i] == ' ' || ret.buff[ret.i] == '\t')
		ret.i++;
	ret.we = ft_strdup(ret.buff + ret.i);
	if (open(ret.we, O_RDONLY) == -1)
	{
		write(1, "Dumb we path\n", 13);
		ret.ok = 0;
	}
	ret.i = 0;
	ret.all++;
	return (ret);
}

t_struct	ftspath(t_struct ret)
{
	if (ret.sok == 1)
	{
		ret.ok = 0;
		write(1, "too much S \n", 13);
		return (ret);
	}
	ret.sok = 1;
	ret.i = ret.i + 1;
	while (ret.buff[ret.i] == ' ' || ret.buff[ret.i] == '\t')
		ret.i++;
	ret.s = ft_strdup(ret.buff + ret.i);
	if (open(ret.s, O_RDONLY) == -1)
	{
		write(1, "Dumb sp path\n", 13);
		ret.ok = 0;
	}
	ret.i = 0;
	ret.all++;
	return (ret);
}
