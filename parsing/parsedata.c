/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsedata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:52:47 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/23 19:41:58 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			valideline(t_struct ret, char c, char *str)
{
	int	i;

	i = ret.i;
	while (ret.buff[i] == ' ' || ret.buff[i] == '\t' ||
			ft_isdigit(ret.buff[i]) == 1 || ret.buff[i] == c)
		i++;
	ret.ok = (i == ft_strlen(ret.buff)) ? ret.ok : 0;
	i = 0;
	while ((str[i] == '\t' || str[i] == ' ' || str[i] == c))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] == '\t' || str[i] == ' ' || str[i] == c))
		i++;
	ret.ok = (str[i] == '\0') ? ret.ok : 0;
	if (ret.ok == 0)
		return (0);
	return (1);
}

t_struct	ftreso(t_struct ret)
{
	ret.i++;
	ret.rok++;
	ret.ok = (valideline(ret, ' ', "\0") == 1) ? ret.ok : 0;
	ret.split = ft_split(ret.buff + ret.i, ' ');
	if (!ret.split[1])
	{
		freesplit(&ret);
		ret.ok = 0;
		return (ret);
	}
	ret.longueur = ft_atoi(ret.split[0]);
	ret.hauteur = ft_atoi(ret.split[1]);
	if (ret.split[2] || (ret.hauteur == 0 || ret.longueur == 0 || ret.rok > 1))
	{
		write(1, "shit happend in R\n", 18);
		ret.ok = 0;
	}
	freesplit(&ret);
	ret.hauteur = (ret.hauteur > HSCREEN) ? HSCREEN : ret.hauteur;
	ret.longueur = (ret.longueur > WSCREEN) ? WSCREEN : ret.longueur;
	ret.i = 0;
	ret.all++;
	return (ret);
}

t_struct	ftfloor(t_struct ret)
{
	ret.i++;
	ret.fok++;
	ret.split = ft_split(ret.buff + ret.i, ',');
	if (!ret.split[2])
	{
		freesplit(&ret);
		ret.ok = 0;
		return (ret);
	}
	ret.f[0] = ft_atoi(ret.split[0]);
	ret.ok = (valideline(ret, ',', ret.split[0]) == 1) ? ret.ok : 0;
	ret.f[1] = ft_atoi(ret.split[1]);
	ret.ok = (valideline(ret, ',', ret.split[1]) == 1) ? ret.ok : 0;
	ret.f[2] = ft_atoi(ret.split[2]);
	ret.ok = (valideline(ret, ',', ret.split[2]) == 1) ? ret.ok : 0;
	if (ret.ok == 0 || ret.f[0] > 255 || ret.f[1] > 255 || ret.f[2] > 255 ||
			ret.split[3] || ret.fok > 1)
	{
		write(1, "shit happend in F\n", 18);
		ret.ok = 0;
	}
	freesplit(&ret);
	ret.i = 0;
	ret.all++;
	return (ret);
}

t_struct	ftski(t_struct ret)
{
	ret.skiok++;
	ret.i++;
	ret.split = ft_split(ret.buff + ret.i, ',');
	if (!ret.split[2])
	{
		freesplit(&ret);
		ret.ok = 0;
		return (ret);
	}
	ret.c[0] = ft_atoi(ret.split[0]);
	ret.ok = (valideline(ret, ',', ret.split[0]) == 1) ? ret.ok : 0;
	ret.c[1] = ft_atoi(ret.split[1]);
	ret.ok = (valideline(ret, ',', ret.split[1]) == 1) ? ret.ok : 0;
	ret.c[2] = ft_atoi(ret.split[2]);
	ret.ok = (valideline(ret, ',', ret.split[2]) == 1) ? ret.ok : 0;
	if (ret.ok == 0 || ret.c[0] > 255 || ret.c[1] > 255 || ret.c[2] > 255 ||
			ret.split[3] || ret.skiok > 1)
	{
		write(1, "shit happend in c\n", 18);
		ret.ok = 0;
	}
	freesplit(&ret);
	ret.i = 0;
	ret.all++;
	return (ret);
}

t_struct	initstrut(t_struct ret)
{
	ret.end = 1;
	ret.m = 0;
	ret.all = 0;
	ret.i = 0;
	ret.count = 0;
	ret.len = 0;
	ret.ok = 2;
	ret.nook = 0;
	ret.sook = 0;
	ret.eaok = 0;
	ret.weok = 0;
	ret.sok = 0;
	ret.fok = 0;
	ret.rok = 0;
	ret.skiok = 0;
	return (ret);
}
