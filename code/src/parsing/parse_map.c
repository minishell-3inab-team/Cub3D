/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabusnin <aabusnin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:05:43 by aabusnin          #+#    #+#             */
/*   Updated: 2026/04/26 18:19:04 by aabusnin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0');
}

static int	is_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	return (ft_strchr("10NSEW", s[i]) != NULL);
}

static void	set_player_dir(t_game *g, char c)
{
	if (c == 'N')
		g->player.dir_x = 0, g->player.dir_y = -1, g->player.plane_x = 0.66, g->player.plane_y = 0;
	else if (c == 'S')
		g->player.dir_x = 0, g->player.dir_y = 1, g->player.plane_x = -0.66, g->player.plane_y = 0;
	else if (c == 'E')
		g->player.dir_x = 1, g->player.dir_y = 0, g->player.plane_x = 0, g->player.plane_y = 0.66;
	else if (c == 'W')
		g->player.dir_x = -1, g->player.dir_y = 0, g->player.plane_x = 0, g->player.plane_y = -0.66;
}

static int process_id(t_game *g, char *line)
{
    if (!ft_strncmp(line, "NO ", 3))
        g->no_path = ft_strtrim(line + 2, " \t\n");
    else if (!ft_strncmp(line, "SO ", 3))
        g->so_path = ft_strtrim(line + 2, " \t\n");
    else if (!ft_strncmp(line, "EA ", 3))
        g->ea_path = ft_strtrim(line + 2, " \t\n");
    else if (!ft_strncmp(line, "WE ", 3))
        g->we_path = ft_strtrim(line + 2, " \t\n");
    else if (!ft_strncmp(line, "F ", 2))
        g->floor_color = parse_color(line + 1);
    else if (!ft_strncmp(line, "C ", 2))
        g->ceil_color = parse_color(line + 1);
    else
        return (0);
    return (1);
}

static int  init_player_from_map(t_game *g)
{
    int r;
    int c;
    int cnt;

    r = 0;
    cnt = 0;
    while (r < g->map.rows)
    {
        c = 0;
        while (g->map.grid[r][c])
        {
            if (ft_strchr("NSEW", g->map.grid[r][c]))
            {
                cnt++;
                g->player.x = c + 0.5;
                g->player.y = r + 0.5;
                set_player_dir(g, g->map.grid[r][c]);
            }
            c++;
        }
        r++;
    }
    return (cnt == 1);
}

static int read_map_lines(t_game *g, int fd)
{
    char    *line;
    int     i;

    i = 0;
    g->map.cols = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (!is_empty(line) && !process_id(g, line) && is_map_line(line))
        {
            g->map.grid[i] = ft_strtrim(line, "\n");
            if (!g->map.grid[i])
                return (free(line), 0);
            if ((int)ft_strlen(g->map.grid[i]) > g->map.cols)
                g->map.cols = (int)ft_strlen(g->map.grid[i]);
            i++;
        }
        free(line);
    }
    g->map.grid[i] = NULL;
    g->map.rows = i;
    return (1);
}

int parse_map(t_game *game, char *av)
{
    int fd;

    game->floor_color = -1;
    game->ceil_color = -1;
    fd = open(av, O_RDONLY);
    if (fd < 0)
        return (0);
    game->map.grid = malloc(sizeof(char *) * 4096);
    if (!game->map.grid)
        return (close(fd), 0);
    if (!read_map_lines(game, fd))
        return (close(fd), 0);
    close(fd);
    if (game->map.rows == 0 || !game->no_path || !game->so_path \
        || !game->ea_path || !game->we_path)
        return (0);
    if (game->floor_color == -1 || game->ceil_color == -1)
        return (0);
    return (init_player_from_map(game));
}

/* static int	init_player_from_map(t_game *g)
{
	int	r;
	int	c;
	int	cnt;

	r = 0;
	cnt = 0;
	while (r < g->map.rows)
	{
		c = 0;
		while (g->map.grid[r][c])
		{
			if (ft_strchr("NSEW", g->map.grid[r][c]))
			{
				cnt++;
				g->player.x = c + 0.5;
				g->player.y = r + 0.5;
				set_player_dir(g, g->map.grid[r][c]);
				// g->map.grid[r][c] = '0';
			}
			c++;
		}
		r++;
	}
	return (cnt == 1);
}

int	parse_map(t_game *game, char *av)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map.grid = malloc(sizeof(char *) * 4096);
	if (!game->map.grid)
		return (close(fd), 0);
	i = 0;
	game->map.cols = 0;
	while ((line = get_next_line(fd)) != NULL)
    {
        if (!is_empty(line) && !ft_strncmp(line, "NO ", 3))
            game->no_path = ft_strtrim(line + 2, " \t\n");
        else if (!is_empty(line) && !ft_strncmp(line, "SO ", 3))
            game->so_path = ft_strtrim(line + 2, " \t\n");
        else if (!is_empty(line) && !ft_strncmp(line, "EA ", 3))
            game->ea_path = ft_strtrim(line + 2, " \t\n");
        else if (!is_empty(line) && !ft_strncmp(line, "WE ", 3))
            game->we_path = ft_strtrim(line + 2, " \t\n");
        else if (!is_empty(line) && is_map_line(line))
        {
            game->map.grid[i] = ft_strtrim(line, "\n");
            if (!game->map.grid[i])
                return (free(line), close(fd), 0);
            if ((int)ft_strlen(game->map.grid[i]) > game->map.cols)
                game->map.cols = (int)ft_strlen(game->map.grid[i]);
            i++;
        }
        free(line);
    }
	game->map.grid[i] = NULL;
	game->map.rows = i;
	close(fd);
	if (game->map.rows == 0 || !game->no_path || !game->so_path || !game->ea_path || !game->we_path)
		return (0);
	if (game->floor_color == -1)
		game->floor_color = 0x333333;
	if (game->ceil_color == -1)
		game->ceil_color = 0x87CEEB;
	return (init_player_from_map(game));
} */
