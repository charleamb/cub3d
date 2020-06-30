/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gosprite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:36:17 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/08 20:54:11 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixeltexsp(t_all *all, t_dda dda, int x, int y)
{
	int (*pix_array)[all->ret->longueur];
	int (*pixtxt_array)[all->img->textw[5]];
	int texture;

	texture = 5;
	all->img->addr[texture] = mlx_get_data_addr(all->img->img[texture],
			&all->img->bpp[texture],
			&all->img->line_length[texture],
			&all->img->endian[texture]);
	pix_array = (void *)all->img->addr[0];
	pixtxt_array = (void *)all->img->addr[texture];
	if (pixtxt_array[dda.texty][dda.textx] != -16777216 &&
			pixtxt_array[dda.texty][dda.textx] != 461842 &&
			pixtxt_array[dda.texty][dda.textx] != 0)
		pix_array[y][x] = pixtxt_array[dda.texty][dda.textx];
}

void	spritelifebis(t_all *all, int i)
{
	all->sp->x[i] = all->vars->rx + 0.5;
	all->sp->y[i] = all->vars->ry + 0.5;
	all->sp->distx[i] = all->vars->rx - all->vars->x + 0.5;
	all->sp->disty[i] = all->vars->ry - all->vars->y + 0.5;
	all->sp->dist[i] = ((all->vars->x - all->sp->x[i]) *
	(all->vars->x - all->sp->x[i]) + (all->vars->y - all->sp->y[i]) *
	(all->vars->y - all->sp->y[i]));
	all->sp->mat[i] = 1.0 /
		(all->vars->planex * all->vars->vy - all->vars->vx * all->vars->planey);
	all->sp->trfox[i] = all->sp->mat[i] * (all->vars->vy *
			all->sp->distx[i] - all->vars->vx * all->sp->disty[i]);
	all->sp->trfoy[i] = all->sp->mat[i] * (-all->vars->planey *
			all->sp->distx[i] + all->vars->planex * all->sp->disty[i]);
	all->sp->order[i] = i;
	all->sp->count = i + 1;
}

void	spritelife(t_all *all)
{
	static int	i;
	int			test;
	int			already;

	test = 0;
	already = 0;
	if (i == SPRITE)
	{
		write(1, "error to much sprite\n-increase SPRITE\n", 38);
		freeret(all->ret);
		exit(0);
	}
	i = (all->sp->restart + all->sp->count == (SPRITE + 10)) ? 0 : i;
	spritelifebis(all, i);
	if (i > 0)
		while (test < i - 1)
		{
			if (all->sp->x[i] == all->sp->x[test] &&
					all->sp->y[i] == all->sp->y[test])
				already++;
			test++;
		}
	i = (already == 0) ? i + 1 : i;
}

void	stripe(t_all *all, t_dda dda, int i, int w)
{
	int	stripe;
	int	y;
	int	d;

	stripe = all->sp->drawsx;
	while (stripe < all->sp->drawex)
	{
		dda.textx = (int)(256 * (stripe - (-all->sp->spw / 2 + all->sp->spscx))
				* all->img->textw[5] / all->sp->spw) / 256;
		y = all->sp->drawsy;
		if (all->sp->trfoy[i] > 0 && stripe > 0 && stripe < w &&
				all->sp->trfoy[i] < all->sp->zbuf[stripe])
			while (y < all->sp->drawey)
			{
				d = (y) * 256 - all->ret->hauteur * 128 + all->sp->sph * 128;
				dda.texty = ((d * all->img->texth[5]) / all->sp->sph) / 256;
				ft_put_pixeltexsp(all, dda, stripe, y);
				y++;
			}
		stripe++;
	}
}

void	gosprite(t_all *all, t_dda dda, int w, int h)
{
	int	i;

	trisprite(all);
	i = all->sp->count;
	while (i-- > 1)
	{
		all->sp->spscx =
		(int)((w / 2) * (1 + all->sp->trfox[i] / all->sp->trfoy[i]));
		all->sp->sph = abs((int)(h / (all->sp->trfoy[i])));
		all->sp->drawsy = -all->sp->sph / 2 + h / 2;
		if (all->sp->drawsy < 0)
			all->sp->drawsy = 0;
		all->sp->drawey = all->sp->sph / 2 + h / 2;
		if (all->sp->drawey >= h)
			all->sp->drawey = h - 1;
		all->sp->spw = abs((int)(h / (all->sp->trfoy[i])));
		all->sp->drawsx = -all->sp->spw / 2 + all->sp->spscx;
		if (all->sp->drawsx < 0)
			all->sp->drawsx = 0;
		all->sp->drawex = all->sp->spw / 2 + all->sp->spscx;
		if (all->sp->drawex >= w)
			all->sp->drawex = w - 1;
		stripe(all, dda, i, w);
	}
	initsp(all);
}
