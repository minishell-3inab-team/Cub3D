/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:05:26 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/26 17:51:57 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int parse_file(t_game *game, char *av)
{
    if (!parse_map(game, av))
    {
        printf("Failed to parse map\n");    
        return (0);
    }
    if (!validate_map(game))
    {
        printf("Failed to validate map\n");
        return (0);
    }
    if (!val_texture(game))
    {
        printf("Failed to validate textures\n");
        return (0);
    }
    return (1);
}
