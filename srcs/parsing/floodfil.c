/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:17:20 by barnaud           #+#    #+#             */
/*   Updated: 2025/10/03 17:02:59 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_borders(char **map, int x, int y)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map[height])
		height++;
	while (map[x][width])
		width++;
	if (y == 0 || map[x][y - 1] == ' ' || map[x][y - 1] == '\n')
		return (0);
	if (map[x][y + 1] == ' ' || map[x][y + 1] == '\n')
		return (0);
	if (x == 0 || map[x - 1][y] == ' ' || map[x - 1][y] == '\n')
		return (0);
	if (x == height - 1 || map[x + 1][y] == ' ' || map[x + 1][y] == '\n')
		return (0);
	return (1);
}

int	check_corners(char **map, int x, int y)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map[height])
		height++;
	while (map[x][width])
		width++;
	if (x == 0 || y == 0 || map[x - 1][y - 1] == ' ' || map[x - 1][y
		- 1] == '\n')
		return (0);
	if (x == 0 || y == width - 1 || map[x - 1][y + 1] == ' ' || map[x - 1][y
		+ 1] == '\n')
		return (0);
	if (x == height - 1 || y == 0 || map[x + 1][y - 1] == ' ' || map[x + 1][y
		- 1] == '\n')
		return (0);
	if (x == height - 1 || y == width - 1 || map[x + 1][y + 1] == ' ' || map[x
		+ 1][y + 1] == '\n')
		return (0);
	return (1);
}

int	map_all_coords_safe(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0' || map[x][y] == 'S' || map[x][y] == 'N'
				|| map[x][y] == 'E' || map[x][y] == 'W')
			{
				if (!check_borders(map, x, y) || !check_corners(map, x, y))
					return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	if (!map)
		return (0);
	while (map[height])
		height++;
	return (height);
}

char	**copy_map(char **map)
{
	int		height;
	char	**new_map;
	int		i;

	height = get_map_height(map);
	if (height == 0)
		return (NULL);
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (NULL);
		}
		i++;
	}
	new_map[height] = NULL;
	return (new_map);
}
