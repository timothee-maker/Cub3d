/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:18:59 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/03 17:14:35 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture(char *path_tex, int i)
{
	int	j;
	int	k;

	j = 0;
	while (path_tex[i] && (path_tex[i] == ' ' || path_tex[i] == '\t'
			|| path_tex[i] == '\n'))
		i++;
	while (path_tex[i + j] && path_tex[i + j] != '\n' && path_tex[i + j] != ' '
		&& path_tex[i + j] != '\t')
		j++;
	k = j + i;
	while (path_tex[k] && (path_tex[k] == ' ' || path_tex[k] == '\t')
		&& path_tex[k] != '\n')
		k++;
	if (path_tex[k] && path_tex[k] != '\n')
		return (NULL);
	return (ft_substr(path_tex, i, j));
}

int	verify_access(t_game *game)
{
	if (access(game->texinfo.north, F_OK) || access(game->texinfo.north, F_OK)
		|| access(game->texinfo.east, F_OK) || access(game->texinfo.west, F_OK))
		return (err_msg("Texture file not valid\n", 0), destroy_win(game, 1), 0);
	return (1);
}

int	fill_wall_textures(t_game *game, t_texinfo *texinfo, char *map, int j)
{
	if (map[j] == 'N' && map[j + 1] == 'O' && !texinfo->north)
		texinfo->north = get_texture(map, j + 2);
	else if (map[j] == 'S' && map[j + 1] == 'O' && !texinfo->south)
		texinfo->south = get_texture(map, j + 2);
	else if (map[j] == 'E' && map[j + 1] == 'A' && !texinfo->east)
		texinfo->east = get_texture(map, j + 2);
	else if (map[j] == 'W' && map[j + 1] == 'E' && !texinfo->west)
		texinfo->west = get_texture(map, j + 2);
	else
		return (free_tab((void **)game->mapinfo.file), 0);
	return (1);
}

int	all_texture(t_game *game)
{
	if (!game->texinfo.ceiling || !game->texinfo.floor || !game->texinfo.north
		|| !game->texinfo.south || !game->texinfo.east || !game->texinfo.west)
		return (err_msg("Miss element in .cub file or invalid element\n", 0),
			destroy_win(game, 1), 0);
	return (1);
}
