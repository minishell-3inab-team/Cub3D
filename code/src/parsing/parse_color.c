/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:17:52 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/26 18:18:01 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void free_split(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return ;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

int parse_color(char *line)
{
    char    **rgb;
    int     r;
    int     g;
    int     b;

    while (*line == ' ' || *line == '\t')
        line++;
    rgb = ft_split(line, ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
        return (free_split(rgb), -1);
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    free_split(rgb);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);
    return ((r << 16) | (g << 8) | b);
}