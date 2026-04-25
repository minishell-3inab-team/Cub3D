/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:57:08 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/25 21:38:20 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <errno.h>
#include "../code/libft/libft.h"
#include "../code/mlx_linux/mlx.h"

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
    double  plane_x;
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

typedef struct s_ray {
    double  cam_x;
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     tex_x;
}   t_ray;

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
    char        *no_path;
    char        *so_path;
    char        *ea_path;
    char        *we_path;
}   t_game;

/***********************************/
/*************PARSING***************/ 
/***********************************/
int		parse_file(t_game *game, char *av);
int		parse_map(t_game *game, char *av);
int		load_texture(t_game *game, t_tex *tex, char *path);
int		load_all_tex(t_game *game);
int		val_texture(t_game *game);
int		validate_map(t_game *game);
void	flood_fill(char **grid, int cols, int rows, int x, int y);
int		player_position(t_game *game, int *x, int *y);
int		check_flood(char **grid, int rows, int cols);


/***********************************/
/*************CLEANUP***************/ 
/***********************************/
void	error_exit(char *msg);
void	cleanup(t_game *game);
int		render_frame(t_game *game);
void	init_game(t_game *game);


/************ engine/raycaster.c ************/
void	raycaster(t_game *game);
void	draw_vertical_line(t_game *game, int x, int draw_start, int draw_end,
			int color);

/************ engine/render.c ************/
void	ft_pixel_put(t_game *game, int x, int y, int color);

/************ engine/textures.c ************/
int		get_tex_color(t_tex *tex, int x, int y);

/************ hooks/hooks.c ************/
int		setup_hooks(t_game *game);
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);






#endif
