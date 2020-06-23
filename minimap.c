/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:32:37 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/12 17:55:46 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	varsminiplus(t_all *all, int m, int i)
{
	if (all->ret->map[m][i] == 'W')
	{
		all->vars->vx = -1;
		all->vars->vy = 0;
		all->vars->planex = 0;
		all->vars->planey = -0.66;
	}
	if (all->ret->map[m][i] == 'S')
	{
		all->vars->vx = 0;
		all->vars->vy = 1;
		all->vars->planex = -0.66;
		all->vars->planey = 0;
	}
}

void	varsmini(t_all *all, int m, int i)
{
	all->vars->x = (all->vars->x == 0) ? i + 0.5 : all->vars->x;
	all->vars->y = (all->vars->y == 0) ? m + 0.5 : all->vars->y;
	if (all->ret->map[m][i] == 'E')
	{
		all->vars->vx = 1;
		all->vars->vy = 0;
		all->vars->planex = 0;
		all->vars->planey = 0.66;
	}
	if (all->ret->map[m][i] == 'N')
	{
		all->vars->vx = 0;
		all->vars->vy = -1;
		all->vars->planex = 0.66;
		all->vars->planey = 0;
	}
	varsminiplus(all, m, i);
}

void	minimap(t_all *all)
{
	int		i;
	int		m;

	m = 0;
	while (all->ret->map[m] && m < all->ret->count)
	{
		i = 0;
		while (all->ret->map[m][i] && i < all->ret->len)
		{
			if (all->ret->map[m][i] == 'N' || all->ret->map[m][i] == 'S' ||
					all->ret->map[m][i] == 'W' || all->ret->map[m][i] == 'E')
				varsmini(all, m, i);
			all->ret->map[m][i] = (all->ret->map[m][i] == 'N' ||
					all->ret->map[m][i] == 'S' || all->ret->map[m][i] == 'W' ||
					all->ret->map[m][i] == 'E') ? '0' : all->ret->map[m][i];
			i++;
		}
		m++;
	}
}
