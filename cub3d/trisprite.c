/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trisprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 18:34:33 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/03 19:52:14 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tribis(t_all *all, int a, double tmp)
{
	tmp = all->sp->x[a];
	all->sp->x[a] = all->sp->x[a + 1];
	all->sp->x[a + 1] = tmp;
	tmp = all->sp->distx[a];
	all->sp->distx[a] = all->sp->distx[a + 1];
	all->sp->distx[a + 1] = tmp;
	tmp = all->sp->y[a];
	all->sp->y[a] = all->sp->y[a + 1];
	all->sp->y[a + 1] = tmp;
	tmp = all->sp->disty[a];
	all->sp->disty[a] = all->sp->disty[a + 1];
	all->sp->disty[a + 1] = tmp;
	tmp = all->sp->mat[a];
	all->sp->mat[a] = all->sp->mat[a + 1];
	all->sp->mat[a + 1] = tmp;
	tmp = all->sp->trfox[a];
	all->sp->trfox[a] = all->sp->trfox[a + 1];
	all->sp->trfox[a + 1] = tmp;
	tmp = all->sp->trfoy[a];
	all->sp->trfoy[a] = all->sp->trfoy[a + 1];
	all->sp->trfoy[a + 1] = tmp;
}

void	trisprite(t_all *all)
{
	int		a;
	int		b;
	double	tmp;

	b = 0;
	while (b < all->sp->count)
	{
		a = 0;
		while (a < all->sp->count)
		{
			if (all->sp->dist[a] > all->sp->dist[a + 1])
			{
				tmp = all->sp->order[a];
				all->sp->order[a] = all->sp->order[a + 1];
				all->sp->order[a + 1] = tmp;
				tmp = all->sp->dist[a];
				all->sp->dist[a] = all->sp->dist[a + 1];
				all->sp->dist[a + 1] = tmp;
				tribis(all, a, tmp);
			}
			a++;
		}
		b++;
	}
}
