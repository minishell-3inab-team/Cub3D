/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:06:31 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/26 17:52:14 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int val_texture(t_game *game)
{
    if (!load_all_tex(game))
        return (0);
    return (1);
}

int load_texture(t_game *game, t_tex *tex, char *path)
{
    printf("Debug Path: [%s]\n", path); 
    
    tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Failed to load image from this exact path!\n");
        return (0);
    }
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    return (tex->addr != NULL);
}

int load_all_tex(t_game *game)
{
    if (!game->no_path || !game->so_path || !game->ea_path || !game->we_path)
        return (0);
    if (!load_texture(game, &game->tex.north, game->no_path))
        return (0);
    if (!load_texture(game, &game->tex.south, game->so_path))
        return (0);
    if (!load_texture(game, &game->tex.east, game->ea_path))
        return (0);
    if (!load_texture(game, &game->tex.west, game->we_path))
        return (0);
    return (1);
}
