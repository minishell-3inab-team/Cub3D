/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 04:49:35 by jehad             #+#    #+#             */
/*   Updated: 2026/05/13 20:56:03 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	ensure_capacity(t_game *g, int *capacity, int i)
{
	char	**tmp;

	if (i < *capacity - 1)
		return (1);
	*capacity *= 2;
	tmp = realloc(g->map.grid, sizeof(char *) * *capacity);
	if (!tmp)
		return (0);
	g->map.grid = tmp;
	return (1);
}

void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows && grid && grid[i])
	{
		free(grid[i]);
		i++;
	}
	if (grid)
		free(grid);
}
