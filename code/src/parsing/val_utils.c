/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehad <jehad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 04:49:35 by jehad             #+#    #+#             */
/*   Updated: 2026/04/23 04:50:57 by jehad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void flood_fill(t_game *game, int x, int y)
{
    if (x < 0 || x >= game->map.cols || y < 0 || y >= game->map.rows)
        return;
    if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == 'F')
        return;
    game->map.grid[y][x] = 'F';
    flood_fill(game, x + 1, y);
    flood_fill(game, x - 1, y);
    flood_fill(game, x, y + 1);
    flood_fill(game, x, y - 1);
}

int *player_position(t_game *game)
{
    int i;
    int j;
    int pos[2];

    i = 0;
    while (game->map.grid[i])
    {
        j = 0;
        while (game->map.grid[i][j])
        {
            if (ft_strchr("NSEW", game->map.grid[i][j]))
            {        
                pos[0] = j;
                pos[1] = i;
                return (pos);
            }
            j++;
        }
        i++;
    }
    return (NULL);
}
int check_flood(char **grid, int rows, int cols)
{
    int i;
    int j;

    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (grid[i][j] != 'F' && grid[i][j] != '1')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}