/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:41:17 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/25 16:27:24 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*file_header_bmp(int filesize, t_all *all)
{
	char	*bmpfileheader;

	if (!(bmpfileheader = (char*)malloc(14 * sizeof(char))))
	{
		write(1, "error malloc\n", 11);
		freeret(all->ret);
		exit(0);
	}
	ft_memcpy(bmpfileheader, (char[]) {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54,
			0, 0, 0}, 14);
	bmpfileheader[2] = (char)(filesize);
	bmpfileheader[3] = (char)(filesize >> 8);
	bmpfileheader[4] = (char)(filesize >> 16);
	bmpfileheader[5] = (char)(filesize >> 24);
	return (bmpfileheader);
}

char		*info_header_bmp(t_all *all)
{
	char	*bmpinfoheader;

	if (!(bmpinfoheader = (char*)malloc(40 * sizeof(char))))
	{
		write(1, "error malloc\n", 11);
		freeret(all->ret);
		exit(0);
	}
	ft_memcpy(bmpinfoheader, (char[]) {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0}, 40);
	bmpinfoheader[4] = (char)(all->ret->longueur);
	bmpinfoheader[5] = (char)(all->ret->longueur >> 8);
	bmpinfoheader[6] = (char)(all->ret->longueur >> 16);
	bmpinfoheader[7] = (char)(all->ret->longueur >> 24);
	bmpinfoheader[8] = (char)(all->ret->hauteur);
	bmpinfoheader[9] = (char)(all->ret->hauteur >> 8);
	bmpinfoheader[10] = (char)(all->ret->hauteur >> 16);
	bmpinfoheader[11] = (char)(all->ret->hauteur >> 24);
	return (bmpinfoheader);
}

void		write_data(int f, char *data, t_all *all)
{
	int				line;

	line = all->ret->hauteur;
	while (--line + 1)
		write(f, data + all->ret->longueur * line * 4, all->ret->longueur * 4);
}

void		save_bmp(char *data, t_all *all, int ac, char *av)
{
	int				filesize;
	int				f;
	char			*bmpfileheader;
	char			*bmpinfoheader;

	if (ac == 3 && ft_strncmp(av, "--save", 6) == 0)
	{
		filesize = 14 + 40 + 3 * all->ret->longueur * all->ret->hauteur;
		f = open("screened.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
		bmpfileheader = file_header_bmp(filesize, all);
		write(f, bmpfileheader, 14);
		free(bmpfileheader);
		bmpinfoheader = info_header_bmp(all);
		write(f, bmpinfoheader, 40);
		free(bmpinfoheader);
		write_data(f, data, all);
		close(f);
		freeret(all->ret);
		mlx_destroy_window(all->vars->mlx, all->vars->win);
		exit(0);
	}
}
