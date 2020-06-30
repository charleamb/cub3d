/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 19:49:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/11 15:37:26 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	minicondi(t_all *all, int m, int i)
{
	while (all->img->y <= all->img->yb)
	{
		if (all->ret->map[m][i] == '1')
			ft_put_pixel(all, all->img->x + POSX, all->img->y + POSY,
			0x0000000);
		if (all->ret->map[m][i] == '0')
			ft_put_pixel(
					all, all->img->x + POSX, all->img->y + POSY, 0x00FFFFFF);
		if (all->ret->map[m][i] == '2')
			ft_put_pixel(all, all->img->x + POSX, all->img->y + POSY,
			0x000000FF);
		if (all->ret->map[m][i] == 'N' || all->ret->map[m][i] == 'S' ||
				all->ret->map[m][i] == 'W' || all->ret->map[m][i] == 'E')
			varsmini(all, m, i);
		all->img->y++;
	}
	all->ret->map[m][i] = (all->ret->map[m][i] == 'N' ||
			all->ret->map[m][i] == 'S' || all->ret->map[m][i] == 'W' ||
			all->ret->map[m][i] == 'E') ? '0' : all->ret->map[m][i];
}

void	minimap(t_all *all)
{
	int		i;
	int		m;

	m = 0;
	all->img->tiley = (int)((all->ret->hauteur / all->ret->count) / 5);
	all->img->tilex = (int)((all->ret->longueur / all->ret->len) / 5);
	while (all->ret->map[m] && m < all->ret->count)
	{
		i = 0;
		while (all->ret->map[m][i])
		{
			all->img->x = i * all->img->tilex;
			all->img->xb = all->img->x + all->img->tilex;
			while (all->img->x <= all->img->xb)
			{
				all->img->y = m * all->img->tiley;
				all->img->yb = all->img->y + all->img->tiley;
				minicondi(all, m, i);
				all->img->x++;
			}
			i++;
		}
		m++;
	}
}
