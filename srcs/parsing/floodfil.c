/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:17:20 by barnaud           #+#    #+#             */
/*   Updated: 2025/09/29 11:36:39 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				if (!coord_safe(map, x, y))
					return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}

int	coord_safe(char **map, int x, int y)
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

char	**copy_map(char **map)
{
	int		height;
	char	**new_map;
	int		i;

	if (!map)
		return (NULL);
	height = 0;
	while (map[height])
		height++;
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
