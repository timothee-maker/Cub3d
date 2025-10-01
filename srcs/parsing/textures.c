/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:18:59 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/01 11:16:32 by barnaud          ###   ########.fr       */
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

int	verify_access(t_texinfo *texture)
{
	if (access(texture->north, F_OK) || access(texture->north, F_OK)
		|| access(texture->east, F_OK) || access(texture->west, F_OK))
		return (0);
	return (1);
}

int	fill_wall_textures(t_texinfo *texinfo, char *map, int j)
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
		return (0);
	return (1);
}
