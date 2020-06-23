/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:28:29 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/15 17:56:11 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keyleft(t_all *all)
{
	double oldpanex;
	double olddirx;

	olddirx = all->vars->vx;
	oldpanex = all->vars->planex;
	all->vars->vx = all->vars->vx * cos(0.1) - all->vars->vy * sin(0.1);
	all->vars->vy = olddirx * sin(0.1) + all->vars->vy * cos(0.1);
	all->vars->planex =
		all->vars->planex * cos(0.1) - all->vars->planey * sin(0.1);
	all->vars->planey = oldpanex * sin(0.1) + all->vars->planey * cos(0.1);
}

void	keyright(t_all *all)
{
	double oldpanex;
	double olddirx;

	olddirx = all->vars->vx;
	oldpanex = all->vars->planex;
	all->vars->vx = all->vars->vx * cos(-0.1) - all->vars->vy * sin(-0.1);
	all->vars->vy = olddirx * sin(-0.1) + all->vars->vy * cos(-0.1);
	all->vars->planex =
		all->vars->planex * cos(-0.1) - all->vars->planey * sin(-0.1);
	all->vars->planey = oldpanex * sin(-0.1) + all->vars->planey * cos(-0.1);
}

void	keymoov(t_all *all, int key)
{
	if (key == BOT)
	{
		all->vars->y = all->vars->y - all->vars->vy * FAST;
		all->vars->x = all->vars->x - all->vars->vx * FAST;
	}
	else if (key == RIGHT)
	{
		all->vars->y = all->vars->y + all->vars->planey * FAST;
		all->vars->x = all->vars->x + all->vars->planex * FAST;
	}
	else if (key == LEFT)
	{
		all->vars->y = all->vars->y - all->vars->planey * FAST;
		all->vars->x = all->vars->x - all->vars->planex * FAST;
	}
	else if (key == TOP)
	{
		all->vars->y = all->vars->y + all->vars->vy * FAST;
		all->vars->x = all->vars->x + all->vars->vx * FAST;
	}
}

int		onmap(double y, double x, t_all *all)
{
	int	ok;

	ok = 0;
	if ((int)(y) < all->ret->count - 1 && (int)(y) > 0)
		ok++;
	if ((int)(x) < all->ret->len - 1 && (int)(x) > 0)
		ok++;
	return (ok);
}

int		ft_keypressed(t_all *all)
{
	if (all->vars->key[BOT] == 1 && onmap((all->vars->y - all->vars->vy * FAST),
				(all->vars->x - all->vars->vx * FAST), all) == 2)
		keymoov(all, BOT);
	if (all->vars->key[RIGHT] == 1 && onmap((all->vars->y + all->vars->planey
	* FAST), (all->vars->x + all->vars->planex * FAST), all) == 2)
		keymoov(all, RIGHT);
	if (all->vars->key[LEFT] == 1 && onmap((all->vars->y - all->vars->planey
	* FAST), (all->vars->x - all->vars->planex * FAST), all) == 2)
		keymoov(all, LEFT);
	if (all->vars->key[TOP] == 1 && onmap((all->vars->y + all->vars->vy
	* FAST), (all->vars->x + all->vars->vx * FAST), all) == 2)
		keymoov(all, TOP);
	if (all->vars->key[TORIGHT] == 1)
		keyright(all);
	if (all->vars->key[TOLEFT] == 1)
		keyleft(all);
	if (all->vars->key[ECHAP] == 1)
		ft_exit(all);
	loop(all);
	return (1);
}
