/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:03:22 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/22 16:10:14 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        error_exit("Usage: ./cub3D map.cub");
    ft_memset(&game, 0, sizeof(t_game));
    init_game(&game);
    parse_file(&game, argv[1]);
    validate_map(&game);
    load_textures(&game);
    setup_hooks(&game);
    mlx_loop(game.mlx);
    return (0);
}