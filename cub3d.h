/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:33:40 by chgilber          #+#    #+#             */
/*   Updated: 2020/06/23 17:08:41 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdarg.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
//# include <mlx.h>
# include "minilibx_opengl/mlx.h"
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# define TOP 13
# define BOT 1
# define LEFT 0
# define RIGHT 2
# define TORIGHT 123
# define TOLEFT 124
# define ECHAP 53
# define SPRITE 625
# define BIGKEY 2000
# define POSX 0
# define POSY 0
# define ROUGE 15532032
# define FAST 0.2
# define HSCREEN 1400
# define WSCREEN 2570

typedef	struct	s_vars
{
	void		*mlx;
	void		*mlxtxt;
	void		*win;
	double		x;
	double		y;
	double		dirx;
	double		diry;
	int			c;
	int			c0;
	int			key[BIGKEY];
	double		vx;
	double		vy;
	double		ry;
	double		rx;
	double		planex;
	double		planey;
}				t_vars;

typedef	struct	s_data
{
	void		*img[6];
	char		*addr[6];
	char		**imgcol;
	int			bpp[6];
	int			line_length[6];
	int			endian[6];
	int			textw[6];
	int			texth[6];
	float		x;
	float		xb;
	float		y;
	float		yb;
	float		tilex;
	float		tiley;
	int			crgb;
	int			ok;
	int			frgb;
}				t_data;

typedef struct	s_dda
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		lineh;
	int			drawstart;
	int			drawend;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	double		perpwalldist;
	double		stepx;
	double		stepy;
	int			side;
	int			textx;
	int			texty;
	double		wallx;
	double		step;
	int			sprite;
}				t_dda;

typedef	struct	s_struct
{
	int			i;
	int			end;
	int			count;
	int			len;
	int			comp;
	int			all;
	char		*buff;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			nook;
	int			sook;
	int			weok;
	int			eaok;
	int			sok;
	int			fok;
	int			skiok;
	int			rok;
	int			ok;
	int			m;
	int			max;
	int			f[3];
	int			hauteur;
	int			longueur;
	int			c[3];
	char		**map;
	char		**maptmp;
	int			hmax;
	int			lmax;
	char		**split;
}				t_struct;

typedef	struct	s_sprite
{
	double		x[SPRITE];
	double		distx[SPRITE];
	double		y[SPRITE];
	double		disty[SPRITE];
	double		mat[SPRITE];
	double		trfox[SPRITE];
	double		trfoy[SPRITE];
	double		zbuf[WSCREEN];
	double		dist[SPRITE];
	int			order[SPRITE];
	int			count;
	int			restart;
	int			spscx;
	int			sph;
	int			spw;
	int			drawsx;
	int			drawex;
	int			drawsy;
	int			drawey;
}				t_sprite;

typedef struct	s_vect
{
	int			x;
	int			y;
}				t_vect;

typedef	struct	s_all
{
	t_struct	*ret;
	t_data		*img;
	t_vars		*vars;
	t_sprite	*sp;
	t_dda		*dda;
}				t_all;

t_data			colorgb(t_data img, t_struct ret);
t_struct		parse(int fd, char *av, t_struct ret);
t_struct		initret(t_struct ret, char **av);
void			initvars(t_vars *vars, t_struct *ret, char *av);
t_data			initimg(t_vars vars, t_struct ret, t_data img);
t_struct		initstrut(t_struct ret);
t_dda			initdda(t_dda dda);
void			initsp(t_all *all);
t_struct		ftreso(t_struct ret);
t_struct		ftfloor(t_struct ret);
t_struct		ftski(t_struct ret);
t_struct		ftmap(t_struct ret, int fd, char *av);
t_struct		check(t_struct ret);
t_struct		ftnopath(t_struct ret);
t_struct		ftsopath(t_struct ret);
t_struct		fteapath(t_struct ret);
t_struct		ftwepath(t_struct ret);
t_struct		ftspath(t_struct ret);
int				freeret(t_struct *ret);
t_struct		ftdata(t_struct ret, int fd, char *av);
t_struct		checklen(t_struct ret, int fd, char *av);

void			trisprite(t_all *all);
int				nswespace(char map);
void			freesplit(t_struct *ret);
void			errormap(t_struct ret);
int				sidetext(t_dda dda);
void			spritelife(t_all *all);
void			gosprite(t_all *all, t_dda dda, int w, int h);
void			calcdir(t_all *all, t_dda *dda, int x, double w);
void			fillcolor(int x, t_dda dda, t_all *all);
void			ft_put_pixel(t_all *all, int x, int y, int color);
int				ft_exit(t_all *all);
void			ray(t_all *all);
void			droite(t_all *all, float x);
int				ft_keypressed(t_all *all);
int				ft_keyrelease(int keycode, t_all *all);
int				ft_keypress(int keycode, t_all *all);
void			square(t_all *all);
void			dessin(t_data img);
void			minimap(t_all *all);
char			*ft_strcat(char *dest, const char *src, int end);
char			*ft_strcopy(char *dest, const char *src, int end);
void			save_bmp(char *data, t_all *all, int ac, char *av);
void			loop(t_all *all);
#endif
