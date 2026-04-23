/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehad <jehad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:06:42 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/23 04:50:52 by jehad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_map(t_game *game)
{
    if (!check_map1(game))
        return (0);
    if(!check_map2(game))
        return (0);
    if(!check_map3(game))
        return (0);
    return (1);
}

int check_map1(t_game *game)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 0;
    while (game->map.grid[i])
    {
        j = 0;
        while (game->map.grid[i][j])
        {
            if (!ft_strchr("01NSEW ", game->map.grid[i][j]))
                return (0);
            if(ft_strchr("NSEW", game->map.grid[i][j]))
            {
                if(player_count == 1)
                    return (0);
                player_count = 1;
            }
            j++;
        }
        i++;
    }
    return (1);
}

int check_map2(t_game *game)
{
    int row;
    int col;
    int i;

    row = 0;
    col = game->map.cols;
    while(row < game->map.rows)
    {
        if(!(game->map.grid[row][0] == '1') || !(game->map.grid[row][col - 1] == '1'))
            return (0);
        if(row == 0 || row == game->map.rows - 1)
        {
            i = 0;
            while(i < col)
            {
                if(game->map.grid[row][i] != '1')
                    return (0);
                i++;
            }
        }
        row++;
    }
    return (1);
}

int check_map3(t_game *game)
{
    int *pos;
    char **grid;

    grid = ft_strdup(game->map.grid);
    if(grid == NULL)
        return (0);
    pos = player_position(game);
    if (pos == NULL)
        return (0);
    flood_fill(grid, pos[0], pos[1]);
    if(!check_flood(grid, game->map.rows, game->map.cols))
    {
        free(grid);
        return (0);
    }
    free(grid);
    return (1);
}
