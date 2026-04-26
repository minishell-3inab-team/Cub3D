/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:07:03 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/26 17:53:01 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
    ray->cam_x = 2 * x / (double)WIN_WIDTH - 1;
    ray->dir_x = game->player.dir_x + game->player.plane_x * ray->cam_x;
    ray->dir_y = game->player.dir_y + game->player.plane_y * ray->cam_x;
    ray->map_x = (int)game->player.x;
    ray->map_y = (int)game->player.y;
    if (ray->dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1 / ray->dir_x);
    if (ray->dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
}

void	calc_step(t_game *game, t_ray *ray)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
}

static char	map_at(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.rows)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (' ');
	return (game->map.grid[y][x]);
}

void	dda(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (map_at(game, ray->map_y, ray->map_x) == '1'
            || map_at(game, ray->map_y, ray->map_x) == ' ')
            ray->hit = 1;
    }
}


t_tex	*get_wall_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0) 
    {
        if (ray->dir_x > 0)
            return (&game->tex.east);
        return (&game->tex.west);
    }
    else
    {
        if (ray->dir_y > 0)
            return (&game->tex.south);
        return (&game->tex.north);
    }
}

void	calc_texture_x(t_game *game, t_ray *ray, t_tex *tex)
{
    double	wall_x;

    if (ray->side == 0)
        wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
    else
        wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
    wall_x -= floor(wall_x);
    ray->tex_x = (int)(wall_x * (double)tex->width);
    if (ray->side == 0 && ray->dir_x > 0)
        ray->tex_x = tex->width - ray->tex_x - 1;
    if (ray->side == 1 && ray->dir_y < 0)
        ray->tex_x = tex->width - ray->tex_x - 1;
}

void	draw_textured_line(t_game *game, t_ray *ray, t_tex *tex, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = get_tex_color(tex, ray->tex_x, tex_y);
		ft_pixel_put(game, x, y, color);
		y++;
	}
}

void	calc_wall_dimensions(t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
    ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
    ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
    if (ray->draw_end >= WIN_HEIGHT)
        ray->draw_end = WIN_HEIGHT - 1;
}

void	raycaster(t_game *game)
{
    t_ray	ray;
    t_tex	*tex;
    int		x;

    x = 0;
    while (x < WIN_WIDTH)
    {
        init_ray(game, &ray, x);
        calc_step(game, &ray);
        dda(game, &ray);
        calc_wall_dimensions(&ray);
        tex = get_wall_texture(game, &ray);
        calc_texture_x(game, &ray, tex);
        draw_textured_line(game, &ray, tex, x);
        
        x++;
    }
}
