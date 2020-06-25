/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initcub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:19:13 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/25 16:41:57 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		initsp(t_all *all)
{
	int i;

	i = 0;
	while (i < SPRITE)
	{
		all->sp->x[i] = 0;
		all->sp->y[i] = 0;
		all->sp->distx[i] = 0;
		all->sp->disty[i] = 0;
		all->sp->dist[i] = 0;
		all->sp->mat[i] = 0;
		all->sp->trfox[i] = 0;
		all->sp->trfoy[i] = 0;
		all->sp->order[i] = 0;
		all->sp->count = 0;
		i++;
	}
	all->sp->restart = SPRITE + 10;
}

t_struct	initret(t_struct ret, char **av)
{
	int	fd;

	if (ret.i == 1)
	{
		write(1, "no map\n", 7);
		exit(0);
	}
	ret = initstrut(ret);
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || pointcub(av[1]) == -1)
	{
		write(1, "wrong files\n", 10);
		exit(0);
	}
	ret = parse(fd, av[1], ret);
	if (ret.ok == 0)
	{
		write(1, "Error\nMap invalid\n", 19);
		freeret(&ret);
		exit(0);
	}
	return (ret);
}

void		initvars(t_vars *vars)
{
	int w;
	int h;

	w = 0;
	h = 0;
	vars->mlx = mlx_init();
	vars->x = 0;
	vars->y = 0;
	vars->vy = -1;
	vars->vx = 0;
	vars->planex = 0;
	vars->planey = 0.66;
}

t_data		initimg(t_vars vars, t_struct ret, t_data img)
{
	int i;

	i = 0;
	img.addr[0] = mlx_get_data_addr(img.img[0],
			&img.bpp[0], &img.line_length[0], &img.endian[0]);
	img.img[1] = mlx_xpm_file_to_image(vars.mlx,
			ret.no, &img.textw[1], &img.texth[1]);
	img.img[2] = mlx_xpm_file_to_image(vars.mlx,
			ret.so, &img.textw[2], &img.texth[2]);
	img.img[3] = mlx_xpm_file_to_image(vars.mlx,
			ret.we, &img.textw[3], &img.texth[3]);
	img.img[4] = mlx_xpm_file_to_image(vars.mlx,
			ret.ea, &img.textw[4], &img.texth[4]);
	img.img[5] = mlx_xpm_file_to_image(vars.mlx,
			ret.s, &img.textw[5], &img.texth[5]);
	while (i++ <= 5)
		(img.img[i] == 0) ? truefilebf(&ret) : 0;
	img.frgb = 65536 * ret.f[0] + 256 * ret.f[1] + ret.f[2];
	img.crgb = 65536 * ret.c[0] + 256 * ret.c[1] + ret.c[2];
	return (img);
}

t_dda		initdda(t_dda dda)
{
	dda.raydirx = 0;
	dda.raydiry = 0;
	dda.lineh = 0;
	dda.drawstart = 0;
	dda.drawend = 0;
	dda.deltadistx = 0;
	dda.deltadisty = 0;
	dda.sidedistx = 0;
	dda.sidedisty = 0;
	dda.perpwalldist = 0;
	dda.stepx = 0;
	dda.stepy = 0;
	dda.side = 0;
	dda.wallx = 0;
	dda.textx = 0;
	dda.texty = 0;
	dda.step = 0;
	return (dda);
}
