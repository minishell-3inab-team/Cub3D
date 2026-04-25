/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 04:49:35 by jehad             #+#    #+#             */
/*   Updated: 2026/04/25 21:18:19 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	flood_fill(char **grid, int cols, int rows, int x, int y)
{
	char	c;

	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return ;
	if (x >= (int)ft_strlen(grid[y]))
		return ;
	c = grid[y][x];
	if (c == '1' || c == 'F' || c == ' ')
		return ;
	grid[y][x] = 'F';
	flood_fill(grid, cols, rows, x + 1, y);
	flood_fill(grid, cols, rows, x - 1, y);
	flood_fill(grid, cols, rows, x, y + 1);
	flood_fill(grid, cols, rows, x, y - 1);
}

int	player_position(t_game *game, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (ft_strchr("NSEW", game->map.grid[i][j]))
				return (*x = j, *y = i, 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_flood(char **grid, int rows, int cols)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (j >= (int)ft_strlen(grid[i]))
				c = ' ';
			else
				c = grid[i][j];
			if (ft_strchr("0NSEW", c))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
