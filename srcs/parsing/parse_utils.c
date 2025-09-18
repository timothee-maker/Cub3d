/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:24 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/18 11:23:51 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture(char *path_tex, int i)
{
	int		j;
	int		k;

	j = 0;
	while (path_tex[i] && (path_tex[i] == ' ' || path_tex[i] == '\t'
			|| path_tex[i] == '\n'))
		i++;
	while (path_tex[i + j] && (path_tex[i + j] != '\n'
			|| path_tex[i] == ' ' || path_tex[i] == '\t'))
		j++;
	k = j;
	while (path_tex[k] && (path_tex[k] == ' ' || path_tex[k] == '\t'))
		k++;
	if (path_tex[k] && path_tex[k] != '\n')
		return (NULL);
	return (ft_substr(path_tex, i, j));
}

int	fill_direction_textures(t_texinfo *texinfo, char *map, int j)
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
	printf("%s\n", texinfo->north);
	printf("%s\n", texinfo->south);
	printf("%s\n", texinfo->east);
	printf("%s\n", texinfo->west);
	return (1);
}

static int	get_text_map(t_game *game, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !ft_isdigit(map[i][j]))
		{
			if (!fill_direction_textures(&game->texinfo, map[i], j))
				return (err_msg("texture invalide", 0));
			return (2);
		}
		else
		{
			// if (fill_color_textures(game, &game->texinfo, map[i], j) == ERR)
			// 	return (0);
			return (2);
		}
	}
	else if (ft_isdigit(map[i][j]))
	{
		// if (!create_map(game, map, i))
		// 	return (err_msg("invalid map", 0));
		return (0);
	}
	return (4);
}

int	get_file_data(t_game *game, char **map)
{
	t_index	index;

	init_index(&index);
	if (!map || !*map)
		return (0);
	while (map[index.i])
	{
		index.j = 0;
		while (map[index.i][index.j])
		{
			index.k = get_text_map(game, map, index.i, index.j);
			if (index.k == 2)
				break ;
			else if (index.k == 0)
				return (0);
			else if (index.k == 1)
				return (1);
			index.j++;
		}
		index.i++;
	}
	return (1);
}

int	parse_args(char *file, t_game *game)
{
	if (!verify_extension(file))
		return (0);
	if (!parse_data(file, game))
		return (0);
	if (!get_file_data(game, game->map))
		return (0);
	return (1);
}
