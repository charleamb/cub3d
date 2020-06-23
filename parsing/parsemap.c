/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:56:46 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/09 21:03:30 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** ret.comp comparer les lignes adjacentes
** ret.m lignes
** ret.ok = 0 = erreur
*/

t_struct	leftcondi(t_struct ret)
{
	int i;

	i = -1;
	while (i++ < ret.len)
	{
		if (ret.map[ret.m][i] == ' ')
		{
			if (i > 0)
				if (nswespace(ret.map[ret.m][i - 1]) == 0
						|| nswespace(ret.map[ret.m][i + 1]) == 0)
					ret.ok = 0;
			if (ret.m == 0)
				if (nswespace(ret.map[ret.m + 1][i]) == 0)
					ret.ok = 0;
			if (ret.m + 1 == ret.count)
				if (nswespace(ret.map[ret.m - 1][i]) == 0)
					ret.ok = 0;
			if (ret.m > 0 && ret.m + 1 < ret.count)
				if (nswespace(ret.map[ret.m + 1][i]) == 0 ||
						nswespace(ret.map[ret.m - 1][i]) == 0)
					ret.ok = 0;
			ret.map[ret.m][i] = '1';
		}
	}
	return (ret);
}

t_struct	condi(t_struct ret)
{
	if (!(ret.map[ret.m][ret.comp - 1] == '1' ||
				ret.map[ret.m][ret.comp - 1] == ' '))
		ret.ok = 0;
	while (ret.len > ret.comp++)
	{
		if (ret.m == 0)
			if (ret.map[ret.m + 1][ret.comp - 1] == '0')
				ret.ok = 0;
		if (ret.m + 1 == ret.count)
			if (ret.map[ret.m - 1][ret.comp - 1] == '0')
				ret.ok = 0;
		if (ret.m > 0 && ret.m + 1 < ret.count)
			if (ret.map[ret.m + 1][ret.comp - 1] == '0' ||
					ret.map[ret.m - 1][ret.comp - 1] == '0')
				ret.ok = 0;
		ret.map[ret.m] = ft_strcat(ret.map[ret.m], "1", ret.len);
	}
	ret.comp = 0;
	return (ret);
}

/*
** ret.m position de check , ret.max = 0 pour condi , ret.comp pour comparer
** ret.i ligne adjacente
** ret.map tab stock map
*/

t_struct	fillmap(t_struct ret)
{
	ret.m = 0;
	ret.end = 0;
	ret.max = 0;
	while (ret.m < ret.count)
	{
		ret.comp = ft_strlen(ret.map[ret.m]);
		ret.i = ret.comp;
		if (ret.m + 1 < ret.count && ret.m > 0)
			ret.i = ft_strlen(ret.map[ret.m + 1]);
		ret = condi(ret);
		ret = leftcondi(ret);
		ret.m++;
	}
	while (ret.map[0][ret.comp] == '1')
		ret.comp++;
	while (ret.map[ret.m - 1][ret.max] == '1')
		ret.max++;
	ret.ok = (ret.comp == ret.len && ret.max == ret.len) ? ret.ok : 0;
	return (ret);
}

/*
** i et max curseur pour verifier la validiter
** check erreur
*/

t_struct	check(t_struct ret)
{
	ret.i = 0;
	ret.max = ft_strlen(ret.buff) - 1;
	while (ret.buff[ret.i])
	{
		if (ret.buff[ret.i] == '1' || ret.buff[ret.i] == ' ')
			ret.i++;
		else if (ret.buff[ret.i] == '2')
			ret.i++;
		else if (ret.buff[ret.i] == '0')
			ret.i++;
		else if (ret.buff[ret.i] == 'N')
			ret.i++;
		else if (ret.buff[ret.i] == 'S')
			ret.i++;
		else if (ret.buff[ret.i] == 'E')
			ret.i++;
		else if (ret.buff[ret.i] == 'W')
			ret.i++;
		else
			break ;
	}
	ret.i--;
	ret.ok = (ret.i == ret.max) ? ret.ok : 0;
	return (ret);
}

/*
** checklen -> taille de map
** malloc
** ret.end return de gnl
** check  - >verification erreur composition tab
** et boucle gnl pour finir
** fillmap pour map rectangle
*/

t_struct	ftmap(t_struct ret, int fd, char *av)
{
	ret = checklen(ret, fd, av);
	if (ret.ok == 0 || !(ret.map = malloc(sizeof(char *) * ret.count * 2)))
	{
		ret.ok = 0;
		return (ret);
	}
	while (ret.count > ret.m)
	{
		ret = check(ret);
		if (!(ret.map[ret.m] = malloc(sizeof(char) * ret.len * 2)))
		{
			ret.ok = 0;
			return (ret);
		}
		ret.map[ret.m] = ft_strcopy(ret.map[ret.m], ret.buff, ret.len);
		free(ret.buff);
		ret.end = get_next_line(fd, &ret.buff);
		ret.m++;
	}
	if (ret.ok == 0)
		errormap(ret);
	ret = fillmap(ret);
	return (ret);
}
