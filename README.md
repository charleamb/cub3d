# cub3d
little fps 

The setup is made for MAC OS and QWERTY keyboard so if you are under linux  you need to change some line;
in the cub3d.h you need to change :
                                  
                                  line 25 "minilibx_opengl/mlx.h" into "minilibx/mlx.h"
                                  line 28 the define TOP 13 into 119 for qwertylinux / 122 azerty linux.
                                  line 29            BOT 1       115                   115
                                  line 30           LEFT 0       97                    113
                                  line 31          RIGHT 2       100                   100
                                  line 32        TORIGHT 123     65361                 65361
                                  line 33         TOLEFT 124     65363                 65363
                                  line 34         ECHAPT 53      65307                 65307
                                  line 36         BIGKEY 2000    70000                 70000
And you need to rm current libmlx.a  && cd in minilibx : make && cp libmlx.a ../.

so now you can make , and make bonus in current Cub3D , and execute ./Cub3D_Bonus ./map/map.cub (or orther map)
