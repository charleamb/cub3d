/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillcolor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 18:41:54 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/25 18:52:33 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_all *all, int x, int y, int color)
{
	int (*pix_array)[all->ret->longueur];

	pix_array = (void *)all->img->addr[0];
	pix_array[y][x] = color;
}

int		sidetext(t_dda dda)
{
	int texture;

	texture = 4;
	if (dda.side != 0)
	{
		texture = (dda.side == 1) && (texture == 4) ? 1 : texture;
		texture = (dda.side == 3) && (texture == 4) ? 3 : texture;
		texture = (dda.side == 4) && (texture == 4) ? 2 : texture;
	}
	return (texture);
}

void	ft_put_pixeltex(t_all *all, t_dda dda, t_vect vect, int texture)
{
	int (*pix_array);
	int (*pixtxt_array);
	int idx;

	all->img->addr[texture] = mlx_get_data_addr(all->img->img[texture],
			&all->img->bpp[texture],
			&all->img->line_length[texture],
			&all->img->endian[texture]);
	if ((idx = all->ret->longueur * vect.y + vect.x) >=
			all->ret->hauteur * all->ret->longueur)
		idx = all->ret->hauteur * all->ret->longueur;
	if (dda.texty < 1)
		dda.texty = 1;
	pix_array = (void *)all->img->addr[0];
	pixtxt_array = (void *)all->img->addr[texture];
	pix_array[idx] =
		pixtxt_array[all->img->textw[texture] * dda.texty + dda.textx];
}

double	ftabs(double ray)
{
	ray = (ray < 0) ? -ray : ray;
	return (ray);
}

void	fillcolor(int x, t_dda dda, t_all *all)
{
	double	texpos;
	t_vect	vect;

	dda.step = 1.0 * all->img->texth[sidetext(dda)] / dda.lineh;
	texpos = (dda.drawstart - all->ret->hauteur / 2 + dda.lineh / 2) * dda.step;
	vect.y = 0;
	vect.x = x;
	while (vect.y < dda.drawstart)
	{
		ft_put_pixel(all, vect.x, vect.y, all->img->crgb);
		vect.y++;
	}
	while (vect.y < dda.drawend)
	{
		dda.texty = (int)texpos;
		texpos = texpos + dda.step;
		ft_put_pixeltex(all, dda, vect, sidetext(dda));
		vect.y++;
	}
	while (vect.y < all->ret->hauteur)
	{
		ft_put_pixel(all, vect.x, vect.y, all->img->frgb);
		vect.y++;
	}
}
