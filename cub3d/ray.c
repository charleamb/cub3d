/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:02:03 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/15 13:16:36 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sideandh(t_all *all, t_dda *dda, int h)
{
	dda->lineh = (all->ret->hauteur / dda->perpwalldist);
	dda->drawstart = -dda->lineh / 2 + h / 2;
	dda->drawend = dda->lineh / 2 + h / 2;
	if (dda->drawstart < 0)
		dda->drawstart = 0;
	if (dda->drawend >= h)
		dda->drawend = h - 1;
	if (dda->side == 0)
		dda->wallx = all->vars->y + dda->perpwalldist * dda->raydiry;
	else
		dda->wallx = all->vars->x + dda->perpwalldist * dda->raydirx;
	dda->wallx -= floor((dda->wallx));
	dda->textx = dda->wallx * all->img->textw[1];
	if ((dda->side == 0) && dda->raydirx > 0)
		dda->textx = all->img->textw[1] - dda->textx - 1;
	if ((dda->side == 1) && dda->raydiry < 0)
		dda->textx = all->img->textw[1] - dda->textx - 1;
	dda->side = dda->stepx > 0 && dda->side == 0 ? 3 : dda->side;
	dda->side = dda->stepy > 0 && all->vars->ry - all->vars->y > 0
	&& dda->side == 1 ? 4 : dda->side;
}

int		spcheck(t_all *all)
{
	int			boom;

	boom = 0;
	if (all->ret->map[(int)all->vars->ry][(int)all->vars->rx] == '2')
		spritelife(all);
	if (all->ret->map[(int)all->vars->ry][(int)all->vars->rx] == '1')
		boom = 1;
	return (boom);
}

void	ddacalcul(t_all *all, t_dda *dda)
{
	int boom;

	boom = 0;
	while (boom == 0)
	{
		if (dda->sidedistx < dda->sidedisty)
		{
			dda->sidedistx = dda->sidedistx + dda->deltadistx;
			all->vars->rx = all->vars->rx + dda->stepx;
			dda->side = 0;
		}
		else
		{
			dda->sidedisty = dda->sidedisty + dda->deltadisty;
			all->vars->ry = all->vars->ry + dda->stepy;
			dda->side = 1;
		}
		if (all->ret->map[(int)all->vars->ry][(int)all->vars->rx] != '0')
			boom = spcheck(all);
	}
	dda->perpwalldist = (dda->side == 0) ?
		(all->vars->rx - all->vars->x + (1 - dda->stepx) / 2) / dda->raydirx :
		(all->vars->ry - all->vars->y + (1 - dda->stepy) / 2) / dda->raydiry;
}

void	calcdir(t_all *all, t_dda *dda, int x, double w)
{
	all->vars->ry = (int)(all->vars->y);
	all->vars->rx = (int)(all->vars->x);
	dda->camerax = 2 * x / w - 1;
	dda->raydirx = all->vars->vx + all->vars->planex * dda->camerax;
	dda->raydiry = all->vars->vy + all->vars->planey * dda->camerax;
	dda->deltadistx = sqrt(1 + (dda->raydiry * dda->raydiry) /
			(dda->raydirx * dda->raydirx));
	dda->deltadisty = sqrt(1 + (dda->raydirx * dda->raydirx) /
			(dda->raydiry * dda->raydiry));
	dda->stepx = (dda->raydirx < 0) ? -1 : 1;
	dda->sidedistx = (dda->raydirx < 0) ?
		(all->vars->x - all->vars->rx) * dda->deltadistx :
		(all->vars->rx + 1.0 - all->vars->x) * dda->deltadistx;
	dda->stepy = (dda->raydiry < 0) ? -1 : 1;
	dda->sidedisty = (dda->raydiry < 0) ?
		(all->vars->y - all->vars->ry) * dda->deltadisty :
		(all->vars->ry + 1.0 - all->vars->y) * dda->deltadisty;
}

void	ray(t_all *all)
{
	t_dda	dda;
	int		x;
	double	w;
	int		h;

	dda.raydirx = 0;
	x = 0;
	w = all->ret->longueur;
	h = all->ret->hauteur;
	while (x < w)
	{
		dda = initdda(dda);
		calcdir(all, &dda, x, w);
		ddacalcul(all, &dda);
		sideandh(all, &dda, h);
		fillcolor(x, dda, all);
		all->sp->zbuf[x] = dda.perpwalldist;
		x++;
	}
	if (all->sp->count > 0)
		gosprite(all, dda, w, h);
	minimap(all);
	droite(all, x);
}
