/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:00:40 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/25 16:42:00 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop(t_all *all)
{
	minimap(all);
	ray(all);
	mlx_put_image_to_window(
			all->vars->mlx, all->vars->win, all->img->img[0], 0, 0);
}

int		ft_exit(t_all *all)
{
	mlx_destroy_window(all->vars->mlx, all->vars->win);
	freeret(all->ret);
	exit(0);
}

void	window(t_vars *vars, t_struct *ret, t_data *img, char *av)
{
//	mlx_get_screen_size(vars->mlx, &w, &h);
//	ret->longueur = (ret->longueur > w) ? w : ret->longueur;
//	ret->hauteur = (ret->hauteur > h) ? h : ret->hauteur;
	vars->win = mlx_new_window(vars->mlx, ret->longueur, ret->hauteur, av);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img[0], 0, 0);
}

int		main(int ac, char **av)
{
	t_struct	ret;
	t_data		img;
	t_vars		vars;
	t_all		all;
	t_sprite	sp;

	ret.i = ac;
	ret = initret(ret, av);
	initvars(&vars);
	img.img[0] = mlx_new_image(vars.mlx, ret.longueur, ret.hauteur);
	img = initimg(vars, ret, img);
	all.img = &img;
	all.ret = &ret;
	all.vars = &vars;
	all.sp = &sp;
	minimap(&all);
	ray(&all);
	save_bmp(img.addr[0], &all, ac, av[2]);
	window(&vars, &ret, &img, av[1]);
	mlx_hook(vars.win, 33, 1L << 17, (*ft_exit), &all);
	mlx_hook(vars.win, 2, 1L << 0, (*ft_keypress), &all);
	mlx_hook(vars.win, 3, 1L << 1, (*ft_keyrelease), &all);
	mlx_loop_hook(vars.mlx, (*ft_keypressed), &all);
	mlx_loop(vars.mlx);
}
