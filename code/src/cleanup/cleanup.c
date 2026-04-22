/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:08:24 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/22 16:11:36 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void    error_exit(char *msg)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}

void    cleanup(t_game *game)
{
    /* free map grid */
    /* destroy mlx images */
    /* destroy window */
    /* mlx_destroy_display */
    /* free(mlx) */
}