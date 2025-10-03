/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:24 by tnolent           #+#    #+#             */
/*   Updated: 2025/10/03 13:02:03 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_closed(char **map)
{
	char	**tmp_map;

	tmp_map = copy_map(map);
	if (!tmp_map)
		return (err_msg("Erreur copie map\n", 0));
	if (!map_all_coords_safe(tmp_map))
	{
		free_tab((void **)tmp_map);
		return (err_msg("Map ouverte\n", 0));
	}
	free_tab((void **)tmp_map);
	return (1);
}

int	create_map(t_game *game, char **map, int i)
{
	int	j;
	int	k;
	int	flag;
	int	biggest;

	k = 0;
	flag = 0;
	game->mapinfo.start_of_map = i;
	biggest = get_biggest_line(map, i);
	if (!check_map_lines(map, i, &flag, &j))
		return (0);
	if (!check_map_user(flag))
		return (0);
	game->mapinfo.end_of_map = j;
	if (!check_map_after(map, j, k))
		return (0);
	if (!alloc_and_fill_map(game, map, i))
		return (0);
	if (!check_map_closed(game->map))
		return (0);
	return (2);
}

int	get_text_map(t_game *game, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !ft_isdigit(map[i][j]))
		{
			if (!fill_wall_textures(&game->texinfo, map[i], j))
				return (err_msg("texture invalide", 0));
			return (2);
		}
		else
		{
			if (!fill_view_texture(&game->texinfo, map[i], j))
				return (0);
			return (2);
		}
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (!create_map(game, map, i))
			return (0);
		return (1);
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
	if (!get_file_data(game, game->mapinfo.file))
		return (0);
	if (!verify_access(&game->texinfo))
		return (free_tex(&game->texinfo), 0);
	free_tab((void **)game->mapinfo.file);
	return (1);
}
