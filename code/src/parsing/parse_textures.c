/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehad <jehad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:06:31 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/23 05:57:14 by jehad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int val_texture(t_game *game)
{
    if (!load_all_tex(game))
        return (0);
    return (1);
}

int load_texture(t_game *game, t_tex *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
        error_exit("Failed to load texture");
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    return (1);
}

int load_all_tex(t_game *game)
{
    if (!load_texture(game, &game->tex.north, "../texture/north.xpm"))
        error_exit("Failed to load north texture");
    if (!load_texture(game, &game->tex.south, "../texture/south.xpm"))
        error_exit("Failed to load south texture");
    if (!load_texture(game, &game->tex.east, "../texture/east.xpm"))
        error_exit("Failed to load east texture");
    if (!load_texture(game, &game->tex.west, "../texture/west.xpm"))
        error_exit("Failed to load west texture");
    return (1);
}