/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:00:54 by barnaud           #+#    #+#             */
/*   Updated: 2025/10/03 13:01:43 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_map(t_game *game, char **map, int start)
{
	int	i;
	int	end;

	end = game->mapinfo.end_of_map;
	i = 0;
	while (start < end)
	{
		game->map[i] = ft_strdup(map[start++]);
		if (!game->map[i++])
			return (free_tab((void *)map), 0);
	}
	game->map[i] = NULL;
	return (1);
}

int	alloc_and_fill_map(t_game *game, char **map, int i)
{
	game->map = malloc(sizeof(char *) * (game->mapinfo.end_of_map - i + 1));
	if (!game->map)
		return (err_msg(ERR_MALLOC, 0));
	if (!fill_map(game, map, i))
		return (0);
	return (1);
}
