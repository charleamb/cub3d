# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chgilber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:50:11 by chgilber          #+#    #+#              #
#    Updated: 2020/06/12 15:39:48 by chgilber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
NAME_BONUS = Cub3D_bonus

SRCS =		./parsing/parse.c ./parsing/parsedata.c ./parsing/parsemap.c \
			./parsing/parsepath.c ft_strcat.c keyrelease.c \
			GNL/get_next_line.c GNL/get_next_line_utils.c \
			minimap.c main.c keypress.c initcub.c ray.c ./parsing/parsemapbiz.c \
			fillcolor.c gosprite.c trisprite.c saver.c minimapray.c
SRCSLIB =	libft/ft_atoi.c libft/ft_lennbr.c libft/ft_strdup.c

SRCS_BONUS = 	./bonus/keypress_bonus.c ./bonus/minimapray_bonus.c \
			 ./bonus/minimap_bonus.c \
			./parsing/parse.c ./parsing/parsedata.c ./parsing/parsemap.c \
			./parsing/parsepath.c ft_strcat.c \
			GNL/get_next_line.c GNL/get_next_line_utils.c \
			main.c  initcub.c ray.c ./parsing/parsemapbiz.c \
			fillcolor.c gosprite.c trisprite.c saver.c keyrelease.c 

INCLUDES = .

LMINX = libmlx.a
LIBFT = ./libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra

# Text format
_DEF = $'\033[0m
_END = $'\033[0m
_GRAS = $'\033[1m
_SOUL = $'\033[4m
_CLIG = $'\033[5m
_SURL = $'\033[7m

# Colors
_BLACK = $'\033[30m
_RED = $'\033[31m
_GREEN = $'\033[32m
_YELLOW = $'\033[33m
_BLUE = $'\033[34m
_PURPLE = $'\033[35m
_CYAN = $'\033[36m
_GREY = $'\033[37m

# Background
_IBLACK = $'\033[40m
_IRED = $'\033[41m
_IGREEN = $'\033[42m
_IYELLOW = $'\033[43m
_IBLUE = $'\033[44m
_IPURPLE = $'\033[45m
_ICYAN = $'\033[46m
_IGREY = $'\033[47m

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DPDCS = $(SRCS:.c=.d) $(SRCS_BONUS:.c=.d)
OBJS_LIB = $(SRCSLIB:.c=.o)

all : $(NAME)
bonus : $(NAME_BONUS)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@echo "$(_END)$(_GREEN) [OK]\t"
	@make -C libft
	@echo "$(_END)$(_GREEN)[Done]"
	gcc $(CFLAGS) -o $@ $(OBJS) $(LMINX) $(LIBFT) -L lmlx -lm -lbsd -lX11 -lXext
#macversion	gcc $(CFLAGS) -L libft -lft -lmlx -framework OpenGL -framework AppKit -o $@ $(OBJS) $(LMINX)

%.o : %.c
	@echo "$(_END)$(_GREEN) [OK]\t"
	$(CC) $(CFLAGS) -I $(INCLUDES) -MMD -o ${<:.c=.o} -c $<

re : 
	@make fclean
	@make all

$(NAME_BONUS) : $(OBJS_BONUS)
	@echo "$(_END)$(_BLUE) [OK]\t"
	@make -C libft
	@echo "$(_END)$(_BLUE)[Done]"
	gcc $(CFLAGS) -o $@ $(OBJS_BONUS) $(LMINX) $(LIBFT) -L -lmlx -lm -lbsd -lX11 -lXext
#macversion	gcc $(CFLAGS) -L libft -lft -lmlx -framework OpenGL -framework AppKit -o $@ $(OBJS_BONUS) $(LMINX)

fclean : clean
	@rm -f $(NAME) $(DPDCS) $(OBJS_BONUS) $(NAME_BONUS)
	@make fclean -C libft

clean :
	@rm -f $(OBJS) $(DPDCS) $(OBJS_BONUS)
	@make clean -C libft


.PHONY : all re fclean clean bonus
