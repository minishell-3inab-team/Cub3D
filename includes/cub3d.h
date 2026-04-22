/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:57:08 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/22 15:57:38 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


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







#endif