/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehad <jehad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:06:42 by aabusnin          #+#    #+#             */
/*   Updated: 2026/05/15 10:44:49 by jehad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	is_valid_neighbor(t_game *game, int r, int c)
{
	int	nr;
	int	nc;

	nr = r - 1;
	nc = c;
	if (nr < 0 || nc >= (int)ft_strlen(game->map.grid[nr])
		|| game->map.grid[nr][nc] == ' ')
		return (0);
	nr = r + 1;
	if (nr >= game->map.rows || nc >= (int)ft_strlen(game->map.grid[nr])
		|| game->map.grid[nr][nc] == ' ')
		return (0);
	nr = r;
	nc = c - 1;
	if (nc < 0 || game->map.grid[nr][nc] == ' ')
		return (0);
	nc = c + 1;
	if (nc >= (int)ft_strlen(game->map.grid[nr])
		|| game->map.grid[nr][nc] == ' ')
		return (0);
	return (1);
}

static int	check_valid_chars(t_game *game)
{
	int	i;
	int	j;
	int	p_cnt;

	i = 0;
	p_cnt = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!ft_strchr("01NSEW ", game->map.grid[i][j]))
				return (0);
			if (ft_strchr("NSEW", game->map.grid[i][j]))
				p_cnt++;
			j++;
		}
		i++;
	}
	return (p_cnt == 1);
}

static int	check_map_neighbors(t_game *game)
{
	int	r;
	int	c;
	int	len;

	r = 0;
	while (r < game->map.rows)
	{
		c = 0;
		len = ft_strlen(game->map.grid[r]);
		while (c < len)
		{
			if (ft_strchr("0NSEW", game->map.grid[r][c])
				&& !is_valid_neighbor(game, r, c))
				return (0);
			c++;
		}
		r++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_valid_chars(game))
		return (0);
	if (!check_map_neighbors(game))
		return (0);
	return (1);
}
