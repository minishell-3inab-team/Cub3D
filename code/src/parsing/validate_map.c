/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:06:42 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/25 21:18:19 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static char	get_cell(t_game *g, int r, int c)
{
	if (r < 0 || r >= g->map.rows)
		return (' ');
	if (c < 0 || c >= (int)ft_strlen(g->map.grid[r]))
		return (' ');
	return (g->map.grid[r][c]);
}

static int	check_map1(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!ft_strchr("01NSEW ", game->map.grid[i][j]))
				return (0);
			if (ft_strchr("NSEW", game->map.grid[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count == 1);
}

static int	check_map2(t_game *game)
{
	int		r;
	int		c;
	char	ch;

	r = 0;
	while (r < game->map.rows)
	{
		c = 0;
		while (c < game->map.cols)
		{
			ch = get_cell(game, r, c);
			if (ft_strchr("0NSEW", ch))
			{
				if (get_cell(game, r - 1, c) == ' ' || get_cell(game, r + 1, c) == ' ')
					return (0);
				if (get_cell(game, r, c - 1) == ' ' || get_cell(game, r, c + 1) == ' ')
					return (0);
			}
			c++;
		}
		r++;
	}
	return (1);
}

static char	**dup_grid(t_game *game)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < game->map.rows)
	{
		cpy[i] = ft_strdup(game->map.grid[i]);
		if (!cpy[i])
			return (NULL);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

static void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows && grid && grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static int	check_map3(t_game *game)
{
	char	**grid;
	int		x;
	int		y;
	int		ok;

	grid = dup_grid(game);
	if (!grid)
		return (0);
	if (!player_position(game, &x, &y))
		return (free_grid(grid, game->map.rows), 0);
	flood_fill(grid, game->map.cols, game->map.rows, x, y);
	ok = check_flood(grid, game->map.rows, game->map.cols);
	free_grid(grid, game->map.rows);
	return (ok);
}

int	validate_map(t_game *game)
{
	if (!check_map1(game))
		return (0);
	if (!check_map2(game))
		return (0);
	if (!check_map3(game))
		return (0);
	return (1);
}
