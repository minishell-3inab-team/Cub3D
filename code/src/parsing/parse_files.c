/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehad <jehad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:05:26 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/23 05:48:43 by jehad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_file(t_game *game, char *av)
{
    if(!validate_map(&game))
        error_exit("Invalid map");
    if(!parse_map(&game,av))
        error_exit("Failed to parse map");
    if(!val_texture(&game))
        error_exit("Failed to load textures");
    return (1);
}