/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehad <jehad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:57:08 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/23 05:58:25 by jehad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "libft.h"
/* structs.h — shared between A and B, frozen after day 1 */

typedef struct s_map {
    char    **grid;
    int     rows;
    int     cols;
}   t_map;

typedef struct s_player {
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;   /* camera plane, perpendicular to dir */
    double  plane_y;
}   t_player;

typedef struct s_tex {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_tex;

typedef struct s_textures {
    t_tex   north;
    t_tex   south;
    t_tex   east;
    t_tex   west;
}   t_textures;

typedef struct s_game {
    void        *mlx;
    void        *win;
    void        *img;
    char        *img_addr;
    int         bpp;
    int         line_len;
    int         endian;
    t_map       map;
    t_player    player;
    t_textures  tex;
    int         floor_color;
    int         ceil_color;
}   t_game;
/***********************************/
/*************PARSING***************/ 
/***********************************/
int parse_file(t_game *game, char *av);
int parse_map(t_game *game, char *av);
int load_texture(t_game *game, t_tex *tex, char *path);
int load_all_tex(t_game *game);
int val_texture(t_game *game);
int validate_map(t_game *game);
void flood_fill(t_game *game, int x, int y);
int *player_position(t_game *game);
int check_flood(char **grid, int rows, int cols);


/***********************************/
/*************CLEANUP***************/ 
/***********************************/
void    error_exit(char *msg);
void    cleanup(t_game *game);






#endif