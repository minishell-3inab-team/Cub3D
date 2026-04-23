/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehad <jehad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:05:43 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/23 05:37:01 by jehad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_map(t_game *game, char *av)
{
    int fd;
    char *line;
    int i;

    fd = open(av, O_RDONLY);
    if (fd < 0)
        return (0);
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        game->map.grid[i] = ft_strdup(line);
        if(!game->map.grid[i])
            return (0);
        i++;
        free(line);
    }
    free(line);
    close(fd);
    return (1);
}
