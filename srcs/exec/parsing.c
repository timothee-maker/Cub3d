/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:50:25 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/08 16:19:45 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);
	map[0] = "1111111111111111111";
	map[1] = "1000000000000000001";
	map[2] = "1000000000111111001";
	map[3] = "1000000000000000001";
	map[4] = "1000000000011111111";
	map[5] = "1000000100000000001";
	map[6] = "1000010000000000001";
	map[7] = "1000000000000000001";
	map[8] = "1000000000000000001";
	map[9] = "1111111111111111111";
	map[10] = NULL;
	return (map);
}

void	draw_map(t_parse *parse, t_cimg *image)
{
	char	**map;
	int		y;
	int		x;

	map = parse->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, 0x0000FF, image);
			x++;
		}
		y++;
	}
}
