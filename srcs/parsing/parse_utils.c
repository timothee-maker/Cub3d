/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:29:24 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/25 10:55:45 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_map(t_game *game, char **map, int start)
{
	int	i;
	int	end;

	end = game->mapinfo.end_of_map - 1;
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

int	create_map(t_game *game, char **map, int i)
{
	int	j;
	int	k;
	int	flag;
	int	biggest;

	game->mapinfo.start_of_map = i;
	flag = 0;
	j = i;
	biggest = 0;
	while (map[j])
	{
		if (ft_strlen(map[j]) > biggest)
			biggest = ft_strlen(map[j]);
		k = -1;
		while (map[j][++k])
		{
			if (!ft_isdigit(map[j][k]) && map[j][k] != ' ' && map[j][k] != '\t'
				&& map[j][k] != '\n')
			{
				if (ft_strchr("NSEW" ,map[j][k]) && !flag)
					flag = 1;
				else
					return (0);
			}
			if (empty_line(map, j, k))
				break ;
		}
		if (empty_line(map, j++, k))
			break ;
	}
	game->mapinfo.end_of_map = j;
	while (map[j])
	{
		if (!empty_line(map, j++, k))
			return (0);
	}
	// ALLER BAPTISTE JE CROIS EN TOIT
	game->map = malloc(sizeof(char *) * game->mapinfo.end_of_map - i + 1);
	if (!game->map)
		return (0);
	if (!fill_map(game, map, i))
		return (0);
	// for (int l = 0;  game->map[l]; l++)
	// 	printf("%s", game->map[l]);
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
			return (err_msg("invalid map", 0));
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
	// free_tab((void **)game->mapinfo.file);
	return (1);
}
