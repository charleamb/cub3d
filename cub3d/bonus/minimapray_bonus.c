/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimapray_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 19:57:37 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/11 15:37:37 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		inmap(t_all *all, int i)
{
	int ok;
	int x;
	int y1;

	ok = 0;
	x = all->vars->x * all->img->tilex + all->img->tilex / 2;
	y1 = all->vars->y * all->img->tiley + all->img->tiley;
	if (((x + POSX) - all->img->tilex / 2 +
	((all->vars->vx * cos(-0.66)) - all->vars->vy * sin(-0.66)) * i) > 0)
		ok++;
	if (((x + POSX) - all->img->tilex / 2 +
	((all->vars->vx * cos(-0.66)) - all->vars->vy * sin(-0.66)) * i) <
	(all->img->tilex * all->ret->len))
		ok++;
	if (((y1 + POSY - all->img->tiley) + (all->vars->vx * sin(-0.66) +
	all->vars->vy * cos(-0.66)) * i) < (all->img->tiley * all->ret->count))
		ok++;
	return (ok);
}

void	droitebis(t_all *all, float x)
{
	float	y1;
	float	i;

	i = 0;
	y1 = all->vars->y * all->img->tiley + all->img->tiley;
	while (i < 15 && inmap(all, i) == 3)
	{
		ft_put_pixel(all, (x + POSX) - all->img->tilex / 2 + all->vars->vx * i,
		(y1 + POSY - all->img->tiley) + all->vars->vy * i, ROUGE);
		i++;
	}
	i = 0;
	while (i < 15 && inmap(all, i) == 3)
	{
		ft_put_pixel(all, (x + POSX) - all->img->tilex / 2 +
		((all->vars->vx * cos(0.66)) - all->vars->vy * sin(0.66)) * i,
		y1 + POSY - all->img->tiley + ((all->vars->vx * sin(0.66) +
		all->vars->vy * cos(0.66)) * i), ROUGE);
		i++;
	}
}

void	droite(t_all *all, float x)
{
	float	y1;
	float	i;

	i = 0;
	x = all->vars->x * all->img->tilex + all->img->tilex / 2;
	y1 = all->vars->y * all->img->tiley + all->img->tiley;
	while (i < 15 && inmap(all, i) == 3)
	{
		ft_put_pixel(all, (x + POSX) - all->img->tilex / 2 +
		((all->vars->vx * cos(-0.66)) - all->vars->vy * sin(-0.66)) * i,
		(y1 + POSY - all->img->tiley) + (all->vars->vx * sin(-0.66)
			+ all->vars->vy * cos(-0.66)) * i, ROUGE);
		i++;
	}
	droitebis(all, x);
}
